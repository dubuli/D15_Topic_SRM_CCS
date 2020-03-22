%model by zhangzehui, output Psi

function [sys,x0,str,ts,simStateCompliance] = sfuntmpl(t,x,u,flag)
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
sizes.NumOutputs     = 1;
sizes.NumInputs      = 2;
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
ts  = [0 0];

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

sys = [];

% end mdlUpdate

%
%=============================================================================
% mdlOutputs
% Return the block outputs.
%=============================================================================
%
function sys=mdlOutputs(t,x,u)

%u(1) int of U
%u(2) theta
thta=0:0.885315:22.132875;
Flux=0:0.01:0.14;
i=[0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0.0605	0.0602	0.0593	0.0576	0.0553	0.052	0.0476	0.0416	0.0345	0.0283	0.0254	0.0236	0.023	0.0224	0.0215	0.0212	0.0218	0.0232	0.0238	0.0241	0.0269	0.0341	0.0412	0.0469	0.0519	0.054
0.1211	0.1204	0.1185	0.1153	0.1105	0.104	0.0952	0.0833	0.0675	0.0551	0.0469	0.0417	0.0388	0.0369	0.0352	0.0345	0.0349	0.0365	0.0374	0.0378	0.0417	0.0518	0.062	0.0706	0.0781	0.0813
0.1816	0.1806	0.1778	0.1728	0.1657	0.1559	0.1428	0.125	0.1041	0.0858	0.0707	0.0602	0.0531	0.0486	0.0454	0.0435	0.0429	0.0436	0.0442	0.0445	0.048	0.0577	0.0679	0.0769	0.085	0.0884
0.2421	0.2408	0.237	0.2304	0.2209	0.208	0.1907	0.1697	0.1474	0.1251	0.1028	0.0848	0.0715	0.0624	0.0563	0.0521	0.0493	0.048	0.0476	0.0475	0.0495	0.0563	0.0643	0.0719	0.0789	0.0819
0.3026	0.301	0.2963	0.2881	0.2764	0.2607	0.2412	0.2188	0.1958	0.1713	0.146	0.121	0.0995	0.0835	0.0723	0.0641	0.0579	0.0535	0.0512	0.0499	0.0496	0.0521	0.0564	0.0614	0.0664	0.0686
0.3634	0.3615	0.3559	0.3464	0.3327	0.3152	0.2941	0.2714	0.2469	0.2202	0.1934	0.1667	0.1404	0.1166	0.0975	0.0833	0.0723	0.0637	0.0583	0.055	0.0519	0.0497	0.0498	0.0515	0.0539	0.055
0.4246	0.4226	0.4163	0.4058	0.3911	0.372	0.3502	0.3267	0.3	0.2731	0.2451	0.2166	0.1886	0.1613	0.1357	0.1134	0.0961	0.0823	0.0726	0.0662	0.06	0.0536	0.0496	0.0481	0.0478	0.0478
0.4911	0.4888	0.4818	0.4699	0.454	0.4346	0.4127	0.3875	0.3596	0.3323	0.3029	0.2737	0.2448	0.2153	0.1866	0.1584	0.1334	0.113	0.0975	0.0866	0.0775	0.0683	0.0614	0.0571	0.0545	0.0536
0.5733	0.5707	0.5631	0.5504	0.5332	0.5127	0.489	0.4636	0.4358	0.4058	0.3755	0.3462	0.3156	0.2842	0.2526	0.2211	0.1913	0.1629	0.1393	0.1208	0.1079	0.0984	0.0904	0.0845	0.0805	0.079
0.6858	0.683	0.6747	0.6615	0.6445	0.6231	0.5971	0.5693	0.5406	0.5109	0.4793	0.4472	0.4148	0.3805	0.3454	0.3139	0.2814	0.2499	0.2193	0.1931	0.1706	0.1542	0.1439	0.1369	0.1324	0.1308
0.8742	0.8711	0.8621	0.8478	0.8281	0.8036	0.7765	0.7468	0.7152	0.6826	0.649	0.6125	0.5754	0.538	0.5016	0.4654	0.429	0.394	0.3601	0.328	0.2986	0.2728	0.2535	0.2412	0.2338	0.2311
1.1477	1.1446	1.1356	1.1208	1.1006	1.0766	1.0491	1.0189	0.9867	0.9528	0.9156	0.8777	0.8397	0.802	0.7641	0.7264	0.6885	0.6519	0.6174	0.5841	0.5523	0.5225	0.4977	0.4789	0.4675	0.4636
1.465	1.462	1.4531	1.4381	1.4186	1.3948	1.3674	1.3379	1.306	1.2708	1.2343	1.1972	1.1598	1.1223	1.0847	1.0475	1.0117	0.9776	0.9449	0.913	0.8833	0.8548	0.8304	0.8099	0.7954	0.7889
1.7829	1.7807	1.7751	1.7624	1.7454	1.7248	1.7025	1.6745	1.641	1.6085	1.5721	1.5357	1.4981	1.4606	1.4238	1.3884	1.3545	1.3217	1.2893	1.2578	1.2287	1.2028	1.1808	1.162	1.1479	1.1408
 ]';
if u(2)>=22.5
    beta=45-u(2);
else
    beta=u(2);
end
iTemp =interp2(Flux,thta,i,u(1),beta,'spline');
if iTemp<0
    iTemp=0;
else
end
sys=iTemp;
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
