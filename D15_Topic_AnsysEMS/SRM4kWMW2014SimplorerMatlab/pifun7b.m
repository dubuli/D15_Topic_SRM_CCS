function [sys,x0,str,ts,simStateCompliance] = pifun7b(t,x,u,flag)

%------------------------------
global iDes_global;
global est_error_global;
global estformer_global;
global flag_global;
global i_global;

switch flag,
  case 0,
    [sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes;
  case 1,
    sys=mdlDerivatives(t,x,u);
  case 2,
    sys=mdlUpdate(t,x,u);
  case 3,
    sys=mdlOutputs(t,x,u);
  case 4,
    sys=mdlGetTimeOfNextVarHit(t,x,u);
  case 9,
    sys=mdlTerminate(t,x,u);
  otherwise
    DAStudio.error('Simulink:blocks:unhandledFlag', num2str(flag));
end


%####################################################################
function [sys,x0,str,ts,simStateCompliance]=mdlInitializeSizes

%--------------------------------
global iDes_global;
global est_error_global;
global estformer_global;
global flag_global;
global i_global;
iDes_global=0;
est_error_global=0;
estformer_global=0;
flag_global=0;
i_global=1;



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
ts  = [1/9600 0];

% Specify the block simStateComliance. The allowed values are:
%    'UnknownSimState', < The default setting; warn and assume DefaultSimState
%    'DefaultSimState', < Same sim state as a built-in block
%    'HasNoSimState',   < No sim state
%    'DisallowSimState' < Error out when saving or restoring the model sim state
simStateCompliance = 'UnknownSimState';

%=============================================================================

function sys=mdlDerivatives(t,x,u)

sys = [];

%=============================================================================
function sys=mdlUpdate(t,x,u)

%--------------------------------
global iDes_global;
global est_error_global;
global estformer_global;
global flag_global;
global i_global;
x_delta=200;
i_max=5;
% iDes_global=iDes_global+1/9600;
iDesTemp=iDes_global;
est_error_global=est_error_global*0.2+(u(2)-estformer_global)*0.8;
if (u(1)-u(2))>x_delta
    iDes_global=229*5;
elseif (u(1)-u(2))<-x_delta
    iDes_global=0;
elseif est_error_global>0   %use est_error and 201 200
    if  est_error_global*x_delta > (u(1)+1-u(2))
        
        if flag_global ~= 1
            flag_global = 1;
            i_global=1;
        else
            i_global=i_global+1;
            if i_global>i_max
                i_global=i_max;
            end
        end

        iDes_global=iDes_global-i_global;
    elseif est_error_global*x_delta < 1
        if flag_global ~= 2
            flag_global = 2;
            i_global=1;
        else
            i_global=i_global+1;
            if i_global>i_max
                i_global=i_max;
            end
        end
      iDes_global=iDes_global+i_global;
    end
elseif est_error_global<0    
        if  est_error_global*x_delta > (u(1)-u(2))
        
        if flag_global ~= 1
            flag_global = 1;
            i_global=1;
        else
            i_global=i_global+1;
            if i_global>i_max
                i_global=i_max;
            end
        end

        iDes_global=iDes_global-i_global;
        elseif est_error_global*x_delta < (u(1)-u(2))
            if flag_global ~= 2
                flag_global = 2;
                i_global=1;
            else
                i_global=i_global+1;
                if i_global>i_max
                    i_global=i_max;
                end
            end
          iDes_global=iDes_global+i_global;
        end
end

if iDes_global>229*5
     iDes_global=229*5;
elseif  iDes_global<0
     iDes_global=-0.001;
end

 iDes_global=iDesTemp*0.5+iDes_global*0.5;

estformer_global=u(2);

% if (u(1)-u(2))>100
%     iDes_global=229*5;
% elseif (u(1)-u(2))<-100
%     iDes_global=0;
% elseif est_error_global*960 > (u(1)-u(2))
%     if flag_global ~= 1
%         flag_global = 1;
%         i_global=1;
%     else
%         i_global=i_global+1;
%         if i_global>5
%             i_global=5;
%         end
%     end
%         
%     iDes_global=iDes_global-i_global;
% elseif est_error_global*960 < (u(1)-u(2))
%     if flag_global ~= 2
%         flag_global = 2;
%         i_global=1;
%     else
%         i_global=i_global+1;
%         if i_global>5
%             i_global=5;
%         end
%     end
%       iDes_global=iDes_global+i_global;
% end
% 
% if iDes_global>229*5
%      iDes_global=229*5;
% elseif  iDes_global<0
%      iDes_global=-0.001;
% end
% 
% estformer_global=u(2);

% if (u(1)-u(2))>300
%     iDes_global=229*5;
% elseif est_error_global*9600 < (u(1)-u(2))
%     iDes_global=iDes_global-10;
%     
% end

% if iDes_global>229*5
%     iDes_global=229*5;
% elseif iDes_global<0
%     iDes_global=-0.001;
% end

sys = [];

%=============================================================================
function sys=mdlOutputs(t,x,u)
global iDes_global;
%u(1) int of U,Psi
%u(2) theta
% if t==0
%     sys=0;
% end
% if t==5
% sys=sys+1;
% end



sys=iDes_global;



%=============================================================================
function sys=mdlGetTimeOfNextVarHit(t,x,u)

sampleTime = 1;    %  Example, set the next hit to be one second later.
sys = t + sampleTime;


%=============================================================================
function sys=mdlTerminate(t,x,u)

sys = [];

% end mdlTerminate
