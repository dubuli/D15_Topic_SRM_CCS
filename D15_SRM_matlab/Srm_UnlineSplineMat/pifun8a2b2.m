% ����7a3�ı�д
function [sys,x0,str,ts,simStateCompliance] = pifun8a2b2(t,x,u,flag)
%SFUNTMPL General M-file S-function template
%   With M-file S-functions, you can define you own ordinary differential
%   equations (ODEs), discrete system equations, and/or just about
%   any type of algorithm to be used within a Simulink block diagram.
%
%   The general form of an M-File S-function syntax is:
%       [SYS,X0,STR,TS,SIMSTATECOMPLIANCE] = SFUNC(T,X,U,FLAG,P1,...,Pn)
%
%   What is returned by SFUNC at a given point in time, T, depends on the
%   value of the FLAG, the current state vector, X, and the current
%   input vector, U.
%
%   FLAG   RESULT             DESCRIPTION
%   -----  ------             --------------------------------------------
%   0      [SIZES,X0,STR,TS]  Initialization, return system sizes in SYS,
%                             initial state in X0, state ordering strings
%                             in STR, and sample times in TS.
%   1      DX                 Return continuous state derivatives in SYS.
%   2      DS                 Update discrete states SYS = X(n+1)
%   3      Y                  Return outputs in SYS.
%   4      TNEXT              Return next time hit for variable step sample
%                             time in SYS.
%   5                         Reserved for future (root finding).
%   9      []                 Termination, perform any cleanup SYS=[].
%
%
%   The state vectors, X and X0 consists of continuous states followed
%   by discrete states.
%
%   Optional parameters, P1,...,Pn can be provided to the S-function and
%   used during any FLAG operation.
%
%   When SFUNC is called with FLAG = 0, the following information
%   should be returned:
%
%      SYS(1) = Number of continuous states.
%      SYS(2) = Number of discrete states.
%      SYS(3) = Number of outputs.
%      SYS(4) = Number of inputs.
%               Any of the first four elements in SYS can be specified
%               as -1 indicating that they are dynamically sized. The
%               actual length for all other flags will be equal to the
%               length of the input, U.
%      SYS(5) = Reserved for root finding. Must be zero.
%      SYS(6) = Direct feedthrough flag (1=yes, 0=no). The s-function
%               has direct feedthrough if U is used during the FLAG=3
%               call. Setting this to 0 is akin to making a promise that
%               U will not be used during FLAG=3. If you break the promise
%               then unpredictable results will occur.
%      SYS(7) = Number of sample times. This is the number of rows in TS.
%
%
%      X0     = Initial state conditions or [] if no states.
%
%      STR    = State ordering strings which is generally specified as [].
%
%      TS     = An m-by-2 matrix containing the sample time
%               (period, offset) information. Where m = number of sample
%               times. The ordering of the sample times must be:
%
%               TS = [0      0,      : Continuous sample time.
%                     0      1,      : Continuous, but fixed in minor step
%                                      sample time.
%                     PERIOD OFFSET, : Discrete sample time where
%                                      PERIOD > 0 & OFFSET < PERIOD.
%                     -2     0];     : Variable step discrete sample time
%                                      where FLAG=4 is used to get time of
%                                      next hit.
%
%               There can be more than one sample time providing
%               they are ordered such that they are monotonically
%               increasing. Only the needed sample times should be
%               specified in TS. When specifying more than one
%               sample time, you must check for sample hits explicitly by
%               seeing if
%                  abs(round((T-OFFSET)/PERIOD) - (T-OFFSET)/PERIOD)
%               is within a specified tolerance, generally 1e-8. This
%               tolerance is dependent upon your model's sampling times
%               and simulation time.
%
%               You can also specify that the sample time of the S-function
%               is inherited from the driving block. For functions which
%               change during minor steps, this is done by
%               specifying SYS(7) = 1 and TS = [-1 0]. For functions which
%               are held during minor steps, this is done by specifying
%               SYS(7) = 1 and TS = [-1 1].
%
%      SIMSTATECOMPLIANCE = Specifices how to handle this block when saving and
%                           restoring the complete simulation state of the
%                           model. The allowed values are: 'DefaultSimState',
%                           'HasNoSimState' or 'DisallowSimState'. If this value
%                           is not speficified, then the block's compliance with
%                           simState feature is set to 'UknownSimState'.


%   Copyright 1990-2007 The MathWorks, Inc.
%   $Revision: 1.18.2.3 $

%
% The following outlines the general structure of an S-function.
%

global iDes_global;
global iDesInt_global;
global iDesIntUp_global;
global thetadvance;
global thetaon_apc;
global thetaon_apc_int;

switch flag,

  %%%%%%%%%%%%%%%%%%
  % Initialization %
  %%%%%%%%%%%%%%%%%%
  case 0,
    [sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes;

  %%%%%%%%%%%%%%%
  % Derivatives %
  %%%%%%%%%%%%%%%
  case 1,
    sys=mdlDerivatives(t,x,u);

  %%%%%%%%%%
  % Update %
  %%%%%%%%%%
  case 2,
    sys=mdlUpdate(t,x,u);

  %%%%%%%%%%%
  % Outputs %
  %%%%%%%%%%%
  case 3,
    sys=mdlOutputs(t,x,u);

  %%%%%%%%%%%%%%%%%%%%%%%
  % GetTimeOfNextVarHit %
  %%%%%%%%%%%%%%%%%%%%%%%
  case 4,
    sys=mdlGetTimeOfNextVarHit(t,x,u);

  %%%%%%%%%%%%%
  % Terminate %
  %%%%%%%%%%%%%
  case 9,
    sys=mdlTerminate(t,x,u);

  %%%%%%%%%%%%%%%%%%%%
  % Unexpected flags %
  %%%%%%%%%%%%%%%%%%%%
  otherwise
    DAStudio.error('Simulink:blocks:unhandledFlag', num2str(flag));

end

% end sfuntmpl

%
%=============================================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the S-function.
%=============================================================================
%
function [sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes
global iDes_global;


global iDesInt_global;
global iDesIntUp_global;
global thetadvance;
global thetaon_apc;
global thetaon_apc_int;

iDes_global=0;
iDesInt_global=0;
iDesIntUp_global=0;
thetadvance=1.5;
thetaon_apc=0;
thetaon_apc_int=0;
%
% call simsizes for a sizes structure, fill it in and convert it to a
% sizes array.
%
% Note that in this example, the values are hard coded.  This is not a
% recommended practice as the characteristics of the block are typically
% defined by the S-function parameters.
%
sizes = simsizes;

sizes.NumContStates  = 0;
sizes.NumDiscStates  = 0;
sizes.NumOutputs     = 5;
sizes.NumInputs      = 8;
sizes.DirFeedthrough = 1;
sizes.NumSampleTimes = 1;   % at least one sample time is needed

sys = simsizes(sizes);

%
% initialize the initial conditions
%
x0  = [];

%
% str is always an empty matrix
%
str = [];

%
% initialize the array of sample times
%
ts  = [1/9600 0];

% Specify the block simStateComliance. The allowed values are:
%    'UnknownSimState', < The default setting; warn and assume DefaultSimState
%    'DefaultSimState', < Same sim state as a built-in block
%    'HasNoSimState',   < No sim state
%    'DisallowSimState' < Error out when saving or restoring the model sim state
simStateCompliance = 'UnknownSimState';

% end mdlInitializeSizes

%
%=============================================================================
% mdlDerivatives
% Return the derivatives for the continuous states.
%=============================================================================
%
function sys=mdlDerivatives(t,x,u)

sys = [];

% end mdlDerivatives

%
%=============================================================================
% mdlUpdate
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function sys=mdlUpdate(t,x,u)
global iDes_global;

global iDesInt_global;
global iDesIntUp_global;
% iDes_global=iDes_global+1/9600;
global thetadvance;
global thetaon_apc;
global thetaon_apc_int;

Uin=514;

iDesInt_global=iDesInt_global+(u(1)-u(2))/8;


if u(6)>8 && u(6)<15
    iDesIntUp_global=iDesIntUp_global*0.9+u(3)*0.1;
end
if u(7)>8 && u(7)<15
    iDesIntUp_global=iDesIntUp_global*0.9+u(4)*0.1;
end
if u(8)>8 && u(8)<15
    iDesIntUp_global=iDesIntUp_global*0.9+u(5)*0.1;
end

%7a3
%if (u(1)-u(2))<1000
% if u(2)>3000
%     if u(1)>u(2)
%         if iDesInt_global>iDesIntUp_global*2
%             iDesInt_global=iDesIntUp_global*2*0.001+iDesInt_global*0.999;
%         end
%     end
% end
if iDesInt_global>229*15
    iDesInt_global=229*15;
elseif iDesInt_global<0
    iDesInt_global=-0.001;
end

iDes_global=(u(1)-u(2))*5+iDesInt_global; %ides output
% if u(2)>3000
%     if u(1)>u(2)
%         if iDes_global>iDesIntUp_global*2
%             iDes_global=iDesIntUp_global*2*0.001+iDesInt_global*0.999;
%         end
%     end
% end

if iDes_global>229*15
    iDes_global=229*15;
elseif iDes_global<0
    iDes_global=-0.001;
end





%   APC
thetadvancetemp=50/1000*iDes_global/229*u(2)/600*360/Uin;
thetadvance=thetadvance*0.99+thetadvancetemp*0.01;

if thetadvance>5
    thetadvance=5;
elseif thetadvance<0
    thetadvance=0;
end



if u(2)>10000
    thetaon_apc_int=thetaon_apc_int+(u(1)-u(2))/10000;
    if thetaon_apc_int>(8-thetadvance)
         thetaon_apc_int=8-thetadvance;
    elseif thetaon_apc_int<(-5-thetadvance)
        thetaon_apc_int=-5-thetadvance;
    end
    thetaon_apc=thetaon_apc_int+(u(1)-u(2))/14000;
     iDesInt_global=iDesInt_global*1.0007;
elseif u(2)>5500
    thetaon_apc_int=thetaon_apc_int+(u(1)-u(2))/8000;
    if thetaon_apc_int>(8-thetadvance)
         thetaon_apc_int=8-thetadvance;
    elseif thetaon_apc_int<(-5-thetadvance)
        thetaon_apc_int=-5-thetadvance;
    end
    thetaon_apc=thetaon_apc_int+(u(1)-u(2))/10000;
     iDesInt_global=iDesInt_global*1.0009;     
     
elseif u(2)<5500
    thetaon_apc=thetaon_apc*0.9999;
    thetaon_apc_int=thetaon_apc_int*0.9999;
    
end

thetadvance=2;
if thetaon_apc>(8-thetadvance)          %�ÿ�ͨ����-1��10֮��
    thetaon_apc=8-thetadvance;
elseif thetaon_apc<(-5-thetadvance)
    thetaon_apc=-5-thetadvance;
end

sys = [];

% end mdlUpdate

%
%=============================================================================
% mdlOutputs
% Return the block outputs.
%=============================================================================
%
function sys=mdlOutputs(t,x,u)
global iDes_global;
global iDesInt_global;
global iDesIntUp_global;
global thetadvance;
global thetaon_apc;
%u(1) int of U,Psi
%u(2) theta
% if t==0
%     sys=0;
% end
% if t==5
% sys=sys+1;
% end

% thetaon_final=thetadvance+thetaon_apc;
% if thetaon_final>5.9
%     thetaon_final=5.9;
% elseif thetaon_final<-5
%     thetaon_final=-5;
% end


sys=[iDes_global,iDesInt_global,iDesIntUp_global,thetadvance,thetaon_apc];
% sys=1.1*229;



% end mdlOutputs

%
%=============================================================================
% mdlGetTimeOfNextVarHit
% Return the time of the next hit for this block.  Note that the result is
% absolute time.  Note that this function is only used when you specify a
% variable discrete-time sample time [-2 0] in the sample time array in
% mdlInitializeSizes.
%=============================================================================
%
function sys=mdlGetTimeOfNextVarHit(t,x,u)

sampleTime = 1;    %  Example, set the next hit to be one second later.
sys = t + sampleTime;

% end mdlGetTimeOfNextVarHit

%
%=============================================================================
% mdlTerminate
% Perform any end of simulation tasks.
%=============================================================================
%
function sys=mdlTerminate(t,x,u)

sys = [];

% end mdlTerminate