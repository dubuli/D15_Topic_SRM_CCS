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

FluxLine20=0:0.1:2.3; 
% thetaRow001=0:0.01:22.5;    % theta 0.01
theta26x1=0:0.9:22.5;  % theta row 50
DeriveThetaofWrow50line20=[0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	0.0999	0.4377	0.9853	1.7334	2.7018	3.8936	5.3078	6.9172	8.6995	10.6338	12.7072	14.9636	17.4829	20.3214	23.5144	27.0738	30.9957	35.2078	39.5215	43.7274	47.6589	51.1842	54.2082
0	0.2231	0.9170	2.0636	3.6628	5.7177	8.2440	11.2479	14.6715	18.4622	22.5686	26.9366	31.6286	36.8146	42.6267	49.1527	56.4328	64.4638	73.1568	82.1597	90.9935	99.2798	106.7147	113.0767
0	0.3594	1.4238	3.2107	5.7140	8.9217	12.8812	17.5942	22.9741	28.9141	35.3175	42.0746	49.1968	56.9239	65.5225	75.1644	85.9500	97.8932	110.9473	124.6942	138.3640	151.2670	162.8601	172.7413
0	0.5206	2.0121	4.5561	8.1613	12.7232	18.3050	24.9632	32.5822	40.9765	49.9582	59.3383	68.9437	78.9384	89.7568	101.7243	115.0624	129.8793	146.1890	163.7645	181.7498	199.0482	214.8199	228.4131
0	0.7131	2.6653	6.1686	10.9085	16.8790	24.3498	33.2537	43.6015	54.9539	66.9880	79.3712	91.7655	103.9797	116.3813	129.6085	144.1032	160.1763	177.9817	197.5638	218.3869	239.1819	258.7008	276.0095
0	0.9709	3.9694	8.8989	16.0950	25.0653	35.5075	47.4833	60.7422	75.2887	90.5840	106.1913	121.6933	136.6566	150.9175	165.0593	179.9777	196.3108	214.4933	234.7689	257.1276	280.5922	303.5145	324.5566
0	1.5648	6.1775	13.5948	23.9052	36.7866	50.5747	65.0237	80.4834	96.7364	113.8986	131.5957	149.4364	167.0264	183.8837	199.8139	215.4892	231.9976	250.1544	270.4824	293.3199	318.4135	344.2489	368.8785
0	1.4402	5.6499	12.6115	22.1562	34.2787	48.7425	63.8836	79.3908	95.8425	113.0601	131.1493	149.8570	168.8067	187.6127	205.7351	222.8749	239.6834	257.3736	276.9130	298.9015	323.7531	350.7698	377.9599
0	0.7277	3.1271	7.1056	12.8522	20.9102	32.0694	46.3566	61.7649	77.5279	94.2514	111.8094	130.2092	149.3519	168.8714	188.3782	207.3077	225.2644	242.8420	261.3478	281.8753	305.1494	331.4784	359.7143
0	0.4620	1.9107	4.3764	7.6976	12.4193	19.2193	29.1892	42.8451	58.3067	74.2266	90.9641	108.6279	127.0330	146.2431	166.0456	186.1060	205.8627	224.8212	243.4559	263.0814	284.8537	309.6559	337.4595
0	0.3178	1.2961	2.9612	5.3189	8.1724	12.0981	17.6205	26.0275	38.4549	53.5387	69.5080	86.1791	103.8091	122.1509	141.3809	161.5167	182.3473	203.3213	223.8288	244.1435	265.4148	288.7982	315.1125
0	0.2415	0.9674	2.1971	3.9307	6.1687	8.7668	12.2792	17.0638	24.1682	35.2020	49.6153	65.5034	82.2006	99.8815	118.2447	137.3899	157.4774	178.4322	199.7704	220.9095	242.0641	264.2688	288.6657
0	0.1828	0.7283	1.6508	2.9654	4.6576	6.7155	9.0499	12.1894	16.4466	22.4157	31.9060	45.2260	60.6610	77.1962	94.7323	112.9516	131.8003	151.5451	172.2905	193.6312	215.0455	236.6828	259.4452
0	0.1430	0.5690	1.2844	2.2994	3.6176	5.2239	7.0971	9.1888	11.9432	15.7470	20.8182	28.8378	40.8658	55.6218	71.8959	89.3552	107.6822	126.6323	146.5280	167.7152	189.8820	212.4108	235.0956
0	0.1170	0.4660	1.0497	1.8743	2.9440	4.2582	5.8030	7.5599	9.5330	12.0631	15.5793	20.1252	26.9997	37.6616	51.4975	67.3085	84.5570	102.7844	121.7145	141.8656	163.6412	186.7528	210.4492
0	0.0965	0.3848	0.8658	1.5442	2.4247	3.5092	4.7928	6.2582	7.8882	9.7315	12.0486	15.2550	19.3671	25.3254	34.7249	47.5490	62.7754	79.8017	98.0455	117.2733	138.1248	160.8053	184.8010
0	0.0809	0.3230	0.7264	1.2927	2.0255	2.9275	3.9997	5.2373	6.6234	8.1458	9.8804	12.0253	14.9408	18.7073	23.9460	32.1415	43.7301	58.0603	74.5983	92.7857	111.8178	132.1323	154.7449
0	0.0681	0.2720	0.6113	1.0871	1.7031	2.4624	3.3672	4.4152	5.5987	6.9003	8.3154	9.9390	11.9338	14.5845	18.0185	22.6661	29.8832	40.3776	53.7444	69.7577	87.2773	105.4962	125.6243
0	0.0595	0.2381	0.5354	0.9514	1.4873	2.1452	2.9271	3.8349	4.8658	6.0148	7.2683	8.6318	10.2009	12.1056	14.5758	17.8155	22.2055	28.7918	38.3199	50.7317	66.2066	83.6459	101.9793
0	0.0504	0.2016	0.4534	0.8054	1.2585	1.8145	2.4743	3.2382	4.1035	5.0632	6.1131	7.2466	8.4947	9.9664	11.7579	14.0179	16.8760	20.7689	26.6848	35.0801	46.2952	60.6175	77.3266
0	0.0439	0.1753	0.3932	0.6970	1.0901	1.5774	2.1608	2.8365	3.5953	4.4222	5.3080	6.2613	7.3055	8.5206	10.0166	11.7908	13.8676	16.3838	19.8828	25.1945	32.6180	42.6075	55.7052
0	0.0385	0.1538	0.3449	0.6110	0.9536	1.3782	1.8895	2.4872	3.1672	3.9159	4.7126	5.5457	6.4157	7.3564	8.4935	9.9533	11.6965	13.6178	15.8793	19.1049	23.8591	30.2739	38.8433
0	0.0282	0.1130	0.2542	0.4513	0.7031	1.0106	1.3778	1.8095	2.3112	2.8871	3.5296	4.2182	4.9309	5.6317	6.3482	7.2119	8.3430	9.7486	11.2147	13.0296	15.6596	19.2584	24.1610
0	0.0129	0.0518	0.1168	0.2079	0.3240	0.4649	0.6326	0.8318	1.0692	1.3547	1.6938	2.0781	2.4867	2.8881	3.2379	3.5718	3.9839	4.5827	5.3316	6.0865	7.0110	8.3894	10.3737
0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0];

if u(1)<=0      %current
    sys=0;
else
    sys=interp2(FluxLine20,theta26x1,DeriveThetaofWrow50line20,u(1),beta,'spline');
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
