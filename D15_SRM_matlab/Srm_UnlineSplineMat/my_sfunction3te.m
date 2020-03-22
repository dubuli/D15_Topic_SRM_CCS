% output Te
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

if u(2)>=22.5
    beta=45-u(2);
else
    beta=u(2);
end

FluxLine20=0:0.08:0.08*19; 
thetaRow001=0:0.01:22.5;    % theta 0.01
thetaRow50=thetaRow001(1:45:2250);  % theta row 50
DeriveThetaofWrow50line20=[0.0000 	0.0260 	0.1047 	0.2355 	0.4186 	0.6534 	0.9444 	1.2827 	1.6626 	2.1037 	2.6100 	3.1565 	3.7108 	4.2821 	4.8868 	5.4590 	5.9069 	6.1838 	6.2825 	6.2360 
0.0000 	0.0857 	0.3432 	0.7722 	1.3726 	2.1447 	3.0874 	4.2010 	5.4792 	6.9317 	8.5721 	10.3624 	12.2673 	14.3831 	16.7650 	19.1563 	21.2226 	22.7810 	23.7745 	24.2799 
0.0000 	0.1478 	0.5915 	1.3309 	2.3657 	3.6970 	5.3190 	7.2394 	9.4525 	11.9602 	14.7805 	17.8578 	21.1314 	24.7705 	28.9154 	33.1477 	36.8668 	39.7320 	41.6215 	42.6471 
0.0000 	0.2123 	0.8496 	1.9117 	3.3980 	5.3103 	7.6392 	10.3978 	13.5824 	17.1891 	21.2351 	25.6428 	30.3033 	35.4443 	41.3379 	47.4331 	52.8395 	57.0366 	59.8234 	61.3374 
0.0000 	0.2855 	1.1423 	2.5705 	4.5690 	7.1404 	10.2724 	13.9857 	18.2715 	23.1187 	28.5497 	34.4654 	40.6754 	47.4283 	55.1924 	63.3549 	70.7066 	76.4914 	80.3864 	82.5217 
0.0000 	0.3783 	1.5140 	3.4066 	6.0554 	9.4635 	13.6159 	18.5513 	24.2335 	30.6353 	37.8105 	45.6475 	53.8242 	62.5291 	72.5217 	83.2801 	93.2378 	101.2835 	106.8783 	110.0673 
0.0000 	0.4512 	1.8055 	4.0626 	7.2217 	11.2860 	16.2439 	22.1433 	28.9347 	36.5803 	45.1117 	54.3613 	63.9480 	74.0411 	85.6286 	98.3659 	110.3837 	120.1742 	127.0014 	130.8592 
0.0000 	0.5003 	2.0020 	4.5045 	8.0077 	12.5133 	18.0200 	24.5650 	32.1104 	40.6199 	50.0487 	60.1287 	70.4722 	81.2425 	93.5806 	107.4752 	120.8173 	131.5971 	138.8943 	142.7349 
0.0000 	0.5845 	2.3392 	5.2629 	9.3563 	14.6196 	21.0585 	28.6684 	37.4281 	47.3101 	58.2879 	70.0400 	81.9155 	93.7511 	107.0050 	122.5568 	137.9855 	150.2702 	158.0845 	161.5563 
0.0000 	0.6915 	2.7669 	6.2249 	11.0672 	17.2919 	24.9089 	33.8647 	44.1959 	55.7857 	68.4679 	82.0358 	95.8421 	109.3056 	123.5881 	140.3297 	157.4972 	171.4850 	180.5080 	184.4651 
0.0000 	0.8008 	3.2042 	7.2088 	12.8171 	20.0254 	28.8447 	39.1933 	51.2086 	64.5258 	78.5164 	93.2802 	108.8267 	124.3422 	139.5452 	156.0924 	173.6024 	189.0825 	200.3902 	206.5906 
0.0000 	0.8914 	3.5661 	8.0234 	14.2653 	22.2897 	32.0970 	43.6266 	56.8557 	71.3718 	86.5593 	102.2874 	118.6014 	134.8569 	150.2441 	166.4296 	184.2975 	201.2274 	214.5585 	222.8572 
0.0000 	0.9721 	3.8879 	8.7483 	15.5538 	24.3045 	34.9873 	47.5640 	61.6811 	76.9307 	93.0081 	109.4164 	125.7914 	141.8919 	157.3086 	173.5409 	192.0871 	210.4872 	225.4052 	235.1972 
0.0000 	1.0700 	4.2788 	9.6292 	17.1198 	26.7479 	38.5032 	52.2624 	67.4853 	83.3827 	99.5568 	116.0905 	132.6993 	149.3587 	166.0550 	183.2967 	202.7780 	222.6999 	239.0450 	249.7238 
0.0000 	1.1807 	4.7220 	10.6269 	18.8929 	29.5136 	42.4437 	57.3595 	73.5108 	89.9986 	106.4646 	122.9854 	139.6444 	156.9016 	174.9256 	193.4172 	213.6807 	234.7152 	252.4405 	264.2552 
0.0000 	1.2776 	5.1107 	11.5012 	20.4462 	31.9357 	45.8414 	61.5720 	78.1379 	94.9784 	111.9974 	128.4935 	144.9758 	162.5264 	181.2763 	200.6947 	221.3700 	243.0439 	262.1480 	275.5052 
0.0000 	1.2649 	5.0605 	11.3876 	20.2461 	31.6152 	45.2958 	60.5622 	76.4577 	92.6672 	108.9135 	125.0896 	141.6997 	159.2106 	177.8059 	196.9635 	217.5760 	240.0151 	260.4807 	274.8313 
0.0000 	1.0936 	4.3749 	9.8442 	17.5033 	27.3363 	39.2019 	52.6682 	67.1277 	82.2955 	97.6564 	113.7004 	130.7747 	148.5482 	166.9785 	185.7649 	206.2147 	229.3258 	251.1555 	266.4088 
0.0000 	0.7617 	3.0462 	6.8542 	12.1845 	19.0579 	27.5846 	38.1891 	50.9080 	65.2749 	80.8413 	97.3604 	115.1427 	133.9368 	152.9833 	172.3404 	192.8666 	216.2657 	239.4355 	256.0445 
0.0000 	0.5820 	2.3269 	5.2354 	9.3058 	14.5670 	21.2192 	29.9781 	41.5213 	55.5890 	71.4612 	88.4397 	106.5519 	125.7591 	145.6074 	165.9218 	186.4972 	209.6036 	233.6761 	252.1892 
0.0000 	0.5514 	2.2046 	4.9600 	8.8180 	13.7892 	20.0021 	27.9427 	38.6624 	52.4368 	68.3109 	85.4731 	103.4659 	122.3847 	142.6374 	163.7381 	184.4310 	206.8920 	231.3300 	251.9279 
0.0000 	0.5197 	2.0788 	4.6767 	8.3160 	12.9945 	18.7726 	25.9938 	35.4515 	47.8788 	63.1230 	79.9771 	97.5608 	115.9527 	135.3736 	156.2514 	177.4190 	199.4289 	223.7067 	245.8095 
0.0000 	0.5200 	2.0804 	4.6802 	8.3225 	13.0021 	18.7392 	25.7298 	34.5026 	45.8561 	60.2750 	76.6539 	93.9138 	112.0253 	130.6236 	150.5747 	171.8643 	193.7391 	217.8414 	241.2848 
0.0000 	0.5416 	2.1661 	4.8732 	8.6643 	13.5395 	19.5096 	26.6095 	35.3085 	46.1313 	59.6297 	75.4819 	92.6171 	110.7409 	129.0700 	147.8922 	168.7485 	190.6844 	214.7972 	239.5267 
0.0000 	0.4734 	1.8931 	4.2583 	7.5705 	11.8313 	17.0444 	23.2387 	30.6936 	40.0915 	52.1470 	67.2688 	84.2447 	101.9844 	120.4033 	139.2699 	159.6631 	181.1858 	205.3479 	230.9368 
0.0000 	0.3683 	1.4726 	3.3118 	5.8871 	9.2004 	13.2509 	18.1039 	23.8638 	31.3468 	41.4507 	55.0509 	71.2924 	88.3955 	106.6987 	126.0409 	146.3030 	167.5394 	191.7045 	217.7453 
0.0000 	0.2894 	1.1573 	2.6022 	4.6244 	7.2268 	10.4102 	14.2029 	18.7033 	24.3888 	32.2144 	43.1605 	57.6873 	74.1001 	91.6734 	111.0687 	131.7245 	153.3605 	177.4072 	203.5539 
0.0000 	0.2514 	1.0056 	2.2611 	4.0175 	6.2774 	9.0437 	12.3189 	16.1927 	20.8983 	27.2343 	36.1976 	48.8159 	64.4252 	81.6471 	100.5985 	121.2770 	143.2742 	167.0136 	192.9755 
0.0000 	0.2445 	0.9782 	2.2001 	3.9090 	6.1067 	8.7971 	11.9779 	15.7048 	20.1289 	25.7601 	33.5358 	44.3515 	58.8710 	75.8427 	94.0784 	114.3021 	136.3066 	159.5591 	185.0196 
0.0000 	0.2420 	0.9683 	2.1786 	3.8709 	6.0468 	8.7097 	11.8555 	15.5116 	19.7845 	24.9619 	31.7518 	41.0929 	53.9323 	69.7611 	87.4724 	106.9731 	128.3551 	150.9933 	175.5808 
0.0000 	0.2305 	0.9226 	2.0765 	3.6901 	5.7635 	8.3004 	11.2998 	14.7656 	18.7717 	23.4858 	29.3955 	37.3786 	48.3111 	62.5635 	79.3901 	98.0720 	118.6365 	140.5951 	164.5968 
0.0000 	0.2077 	0.8314 	1.8721 	3.3278 	5.1964 	7.4824 	10.1915 	13.3120 	16.8868 	21.0541 	26.1646 	32.8562 	41.9406 	54.4390 	69.8649 	87.7060 	107.4743 	128.7715 	152.5961 
0.0000 	0.1874 	0.7501 	1.6893 	3.0036 	4.6902 	6.7521 	9.1968 	12.0168 	15.2270 	18.9266 	23.3693 	29.0397 	36.7774 	47.4561 	61.3914 	78.3527 	97.3852 	118.2563 	141.5739 
0.0000 	0.1659 	0.6642 	1.4959 	2.6603 	4.1547 	5.9801 	8.1428 	10.6455 	13.4842 	16.7203 	20.5289 	25.3045 	31.8307 	40.7367 	52.9803 	68.7293 	87.0692 	107.5832 	130.2543 
0.0000 	0.1399 	0.5598 	1.2607 	2.2423 	3.5021 	5.0403 	6.8618 	8.9711 	11.3610 	14.0726 	17.2083 	21.0862 	26.2156 	33.5137 	43.7791 	57.7575 	75.3751 	95.4165 	117.5608 
0.0000 	0.1204 	0.4818 	1.0851 	1.9302 	3.0148 	4.3385 	5.9052 	7.7202 	9.7792 	12.1041 	14.7559 	17.9834 	22.1706 	28.2137 	36.7602 	48.8850 	65.2842 	84.7092 	106.4840 
0.0000 	0.1153 	0.4614 	1.0389 	1.8482 	2.8872 	4.1553 	5.6551 	7.3912 	9.3637 	11.5810 	14.0987 	17.0800 	20.9058 	26.1872 	33.5876 	44.1732 	59.0106 	77.6515 	99.1163 
0.0000 	0.1336 	0.5345 	1.2032 	2.1401 	3.3442 	4.8158 	6.5557 	8.5606 	10.8311 	13.3857 	16.3043 	19.6127 	23.5866 	28.7590 	35.9110 	45.7969 	59.2306 	76.8642 	97.8402 
0.0000 	0.1399 	0.5597 	1.2594 	2.2391 	3.4989 	5.0409 	6.8660 	8.9646 	11.3281 	13.9740 	17.0037 	20.4252 	24.3096 	29.0927 	35.5662 	44.3231 	55.9919 	71.7421 	91.2592 
0.0000 	0.1218 	0.4873 	1.0957 	1.9468 	3.0410 	4.3828 	5.9751 	7.8078 	9.8565 	12.1171 	14.6896 	17.7076 	21.0220 	24.8577 	29.8669 	36.7608 	46.2382 	59.2261 	76.2567 
0.0000 	0.0961 	0.3842 	0.8636 	1.5335 	2.3943 	3.4502 	4.7060 	6.1568 	7.7767 	9.5470 	11.5278 	13.8917 	16.5720 	19.5348 	23.3545 	28.8189 	36.4043 	46.9423 	61.6806 
0.0000 	0.0800 	0.3197 	0.7185 	1.2758 	1.9912 	2.8674 	3.9102 	5.1222 	6.4847 	7.9703 	9.5810 	11.4713 	13.7729 	16.2872 	19.4252 	23.9390 	30.1535 	38.8379 	51.4928 
0.0000 	0.0855 	0.3419 	0.7691 	1.3665 	2.1334 	3.0706 	4.1836 	5.4809 	6.9534 	8.5685 	10.2754 	12.1976 	14.5708 	17.2500 	20.2718 	24.2132 	29.6652 	37.1846 	47.8684 
0.0000 	0.0878 	0.3515 	0.7918 	1.4093 	2.2028 	3.1693 	4.3109 	5.6394 	7.1656 	8.8680 	10.6660 	12.5845 	14.8667 	17.5888 	20.5244 	24.0150 	28.8400 	35.3321 	44.2400 
0.0000 	0.0827 	0.3312 	0.7475 	1.3338 	2.0890 	3.0057 	4.0794 	5.3222 	6.7662 	8.4164 	10.1935 	11.9953 	13.9851 	16.4877 	19.2252 	22.3140 	26.4697 	31.8975 	39.1833 
0.0000 	0.0727 	0.2915 	0.6591 	1.1792 	1.8517 	2.6675 	3.6152 	4.7006 	5.9609 	7.4322 	9.0752 	10.7327 	12.4265 	14.5062 	16.8915 	19.5871 	22.8918 	27.1214 	32.8079 
0.0000 	0.0488 	0.1958 	0.4434 	0.7948 	1.2504 	1.8032 	2.4418 	3.1667 	4.0057 	4.9995 	6.1418 	7.3036 	8.4309 	9.7592 	11.3588 	13.2083 	15.3357 	18.0634 	21.8368 
0.0000 	0.0136 	0.0546 	0.1238 	0.2221 	0.3497 	0.5044 	0.6822 	0.8828 	1.1147 	1.3933 	1.7204 	2.0572 	2.3731 	2.7305 	3.1951 	3.7739 	4.5216 	5.5687 	7.2010 
0.0000 	-0.0058 	-0.0234 	-0.0529 	-0.0946 	-0.1488 	-0.2147 	-0.2917 	-0.3798 	-0.4814 	-0.5982 	-0.7276 	-0.8572 	-0.9920 	-1.1606 	-1.3333 	-1.4902 	-1.5751 	-1.5852 	-1.3674 
0.0000 	-0.0067 	-0.0269 	-0.0611 	-0.1098 	-0.1731 	-0.2503 	-0.3392 	-0.4394 	-0.5539 	-0.6892 	-0.8474 	-1.0141 	-1.1766 	-1.3582 	-1.5840 	-1.8430 	-2.1365 	-2.4981 	-2.8703 
];

if u(1)<=0
    sys=0;
else
    sys=interp2(FluxLine20,thetaRow50,DeriveThetaofWrow50line20,u(1),beta,'spline');
end


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
