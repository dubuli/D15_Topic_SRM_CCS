% output Psi
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

%u(1) int of U,Psi
%u(2) theta
thta=0:0.72:0.72*31;
Flux=0:0.08:0.08*19;
i=[0.0000 	4.4798 	8.9598 	13.4387 	17.9156 	22.3898 	26.8611 	31.3428 	35.8166 	40.2995 	44.8098 	49.3023 	53.7995 	58.8469 	65.0884 	72.3648 	80.1544 	87.9338 	95.1794 	101.3678 
0.0000 	4.4568 	8.9137 	13.3697 	17.8236 	22.2747 	26.7230 	31.1824 	35.6344 	40.0918 	44.5782 	49.0549 	53.5355 	58.5469 	64.7642 	72.0661 	79.9150 	87.7697 	95.0889 	101.3316 
0.0000 	4.4024 	8.8050 	13.2067 	17.6063 	22.0031 	26.3984 	30.8016 	35.2014 	39.6020 	44.0341 	48.4727 	52.9143 	57.8345 	63.9742 	71.3190 	79.2982 	87.3278 	94.8243 	101.2040 
0.0000 	4.3123 	8.6247 	12.9363 	17.2457 	21.5525 	25.8596 	30.1683 	34.4824 	38.7906 	43.1342 	47.5116 	51.9088 	56.6961 	62.6841 	70.0680 	78.2435 	86.5564 	94.3524 	100.9775 
0.0000 	4.1798 	8.3595 	12.5387 	16.7155 	20.8897 	25.0654 	29.2328 	33.4261 	37.6012 	41.8189 	46.1106 	50.4717 	55.1083 	60.8437 	68.2074 	76.6250 	85.3366 	93.5819 	100.6009 
0.0000 	4.0171 	8.0342 	12.0508 	16.0649 	20.0764 	24.0881 	28.0872 	32.1250 	36.1421 	40.2239 	44.4436 	48.7891 	53.3023 	58.7085 	65.9360 	74.6332 	83.8720 	92.7211 	100.2496 
0.0000 	3.8069 	7.6136 	11.4202 	15.2238 	19.0250 	22.8259 	26.6233 	30.4492 	34.2934 	38.2095 	42.3384 	46.7027 	51.2281 	56.3158 	63.2197 	72.1810 	82.0874 	91.7444 	99.9575 
0.0000 	3.5441 	7.0880 	10.6319 	14.1724 	17.7109 	21.2504 	24.7985 	28.3592 	32.0697 	35.8894 	39.8989 	44.1821 	48.7964 	53.8921 	60.4828 	69.4583 	79.8320 	90.2274 	99.2683 
0.0000 	3.2384 	6.4767 	9.7147 	12.9494 	16.1825 	19.4197 	22.6862 	26.0440 	29.6078 	33.3408 	37.3214 	41.6146 	46.2968 	51.4649 	57.7301 	66.4495 	77.1565 	88.2685 	98.1890 
0.0000 	2.8820 	5.7637 	8.6446 	11.5232 	14.4010 	17.2967 	20.2900 	23.5088 	27.0493 	30.7626 	34.7114 	38.9878 	43.5753 	48.6977 	54.7987 	63.1493 	74.1076 	85.9880 	96.9311 
0.0000 	2.4825 	4.9645 	7.4456 	9.9252 	12.4097 	14.9613 	17.7517 	20.9067 	24.4096 	28.1339 	32.1652 	36.3177 	40.7334 	45.6860 	51.7146 	59.7426 	70.7635 	83.3416 	95.3637 
0.0000 	2.1289 	4.2574 	6.3848 	8.5106 	10.6494 	12.9000 	15.4919 	18.5376 	21.9578 	25.6817 	29.5517 	33.6014 	37.8750 	42.7516 	48.6794 	56.3058 	67.0981 	80.3854 	93.5992 
0.0000 	1.9125 	3.8246 	5.7355 	7.6448 	9.5575 	11.5343 	13.7487 	16.4434 	19.5920 	23.1322 	26.8467 	30.6817 	34.8567 	39.6880 	45.5384 	52.9255 	63.2272 	77.0548 	91.5331 
0.0000 	1.7395 	3.4786 	5.2164 	6.9525 	8.6859 	10.4418 	12.3132 	14.5162 	17.2516 	20.5293 	24.0868 	27.7953 	31.7968 	36.4360 	42.2385 	49.6466 	59.4269 	73.3615 	88.9522 
0.0000 	1.5763 	3.1524 	4.7272 	6.2997 	7.8702 	9.4461 	11.0690 	12.8989 	15.1590 	18.0200 	21.4175 	24.9975 	28.8773 	33.3847 	38.9169 	46.3040 	55.8228 	69.4549 	86.0048 
0.0000 	1.4112 	2.8222 	4.2319 	5.6390 	7.0440 	8.4522 	9.8850 	11.4216 	13.3132 	15.7204 	18.8157 	22.2355 	25.9914 	30.5004 	35.8262 	42.9046 	52.3180 	65.3916 	82.6719 
0.0000 	1.2884 	2.5767 	3.8638 	5.1479 	6.4300 	7.7131 	9.0065 	10.3533 	11.8811 	13.8276 	16.3706 	19.5867 	23.2131 	27.5330 	32.7455 	39.6150 	48.8526 	61.2683 	79.0216 
0.0000 	1.2022 	2.4046 	3.6059 	4.8040 	5.9996 	7.1958 	8.3957 	9.6200 	10.9270 	12.4830 	14.4996 	17.1676 	20.6026 	24.6490 	29.6004 	36.2786 	45.3139 	57.2795 	74.9502 
0.0000 	1.1253 	2.2506 	3.3753 	4.4967 	5.6150 	6.7338 	7.8550 	8.9838 	10.1550 	11.4506 	13.0545 	15.1797 	18.0809 	21.8985 	26.5914 	32.9479 	41.7675 	53.5007 	70.6757 
0.0000 	1.0513 	2.1026 	3.1533 	4.2011 	5.2452 	6.2897 	7.3368 	8.3854 	9.4544 	10.5947 	11.9161 	13.6088 	15.9703 	19.3537 	23.7456 	29.8136 	38.3543 	49.9173 	66.5231 
0.0000 	0.9872 	1.9742 	2.9606 	3.9447 	4.9250 	5.9045 	6.8867 	7.8715 	8.8629 	9.8954 	11.0320 	12.4273 	14.3431 	17.1747 	21.1791 	26.8434 	35.1700 	46.4047 	62.5798 
0.0000 	0.9336 	1.8670 	2.7997 	3.7303 	4.6575 	5.5831 	6.5105 	7.4413 	8.3757 	9.3310 	10.3480 	11.5299 	13.0944 	15.4837 	18.9108 	24.1157 	32.0999 	43.0034 	58.8047 
0.0000 	0.8921 	1.7838 	2.6747 	3.5638 	4.4499 	5.3339 	6.2189 	7.1071 	7.9992 	8.9017 	9.8444 	10.8848 	12.2196 	14.2025 	17.1535 	21.6995 	29.1664 	39.7291 	55.1367 
0.0000 	0.8551 	1.7097 	2.5634 	3.4153 	4.2647 	5.1117 	5.9591 	6.8094 	7.6637 	8.5237 	9.4089 	10.3541 	11.5128 	13.2088 	15.7601 	19.7035 	26.5031 	36.5680 	51.5565 
0.0000 	0.8118 	1.6231 	2.4335 	3.2421 	4.0481 	4.8515 	5.6556 	6.4641 	7.2760 	8.0865 	8.9060 	9.7904 	10.8295 	12.3140 	14.5122 	18.0326 	24.2475 	33.6383 	48.2469 
0.0000 	0.7751 	1.5498 	2.3236 	3.0957 	3.8649 	4.6306 	5.3971 	6.1710 	6.9521 	7.7274 	8.4882 	9.3057 	10.3066 	11.6646 	13.6355 	16.8073 	22.5791 	31.3469 	45.3464 
0.0000 	0.7487 	1.4971 	2.2448 	2.9908 	3.7337 	4.4724 	5.2112 	5.9582 	6.7175 	7.4730 	8.2036 	8.9580 	9.9089 	11.2254 	13.0173 	15.9340 	21.3844 	29.6466 	42.8852 
0.0000 	0.7216 	1.4427 	2.1632 	2.8821 	3.5980 	4.3097 	5.0200 	5.7374 	6.4692 	7.2048 	7.9218 	8.6282 	9.5054 	10.7840 	12.5057 	15.2441 	20.4276 	28.3435 	40.9917 
0.0000 	0.6957 	1.3908 	2.0848 	2.7771 	3.4671 	4.1541 	4.8394 	5.5285 	6.2269 	6.9343 	7.6404 	8.3393 	9.1579 	10.3600 	12.0708 	14.6860 	19.6798 	27.3725 	39.6230 
0.0000 	0.6772 	1.3536 	2.0283 	2.7009 	3.3716 	4.0413 	4.7106 	5.3810 	6.0539 	6.7321 	7.4213 	8.1284 	8.9306 	10.0717 	11.7532 	14.3068 	19.2285 	26.7566 	38.8070 
0.0000 	0.6739 	1.3469 	2.0182 	2.6871 	3.3544 	4.0210 	4.6878 	5.3551 	6.0233 	6.6949 	7.3796 	8.0888 	8.8923 	10.0224 	11.6889 	14.2255 	19.1157 	26.5900 	38.5217 
0.0000 	0.6758 	1.3508 	2.0241 	2.6951 	3.3645 	4.0329 	4.7013 	5.3703 	6.0410 	6.7158 	7.4029 	8.1118 	8.9161 	10.0514 	11.7225 	14.2614 	19.1545 	26.6347 	38.5395 
];
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
