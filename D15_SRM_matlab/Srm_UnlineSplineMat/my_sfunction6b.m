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
thta=0:0.9:22.5;
Flux=0:0.1:2.3;
i=[0	2.8980	5.7959	8.6940	11.5915	14.4877	17.4102	20.3683	23.3196	26.2215	29.0317	31.7143	34.3209	36.9624	39.7509	42.7987	46.2179	50.1205	54.5796	59.5237	64.8484	70.4494	76.2224	82.0629
0	2.8817	5.7594	8.6456	11.5257	14.4057	17.3107	20.2530	23.1903	26.0800	28.8791	31.5504	34.1394	36.7581	39.5206	42.5406	45.9320	49.8087	54.2527	59.1987	64.5396	70.1683	75.9775	81.8600
0	2.8295	5.6519	8.4898	11.3166	14.1448	16.9934	19.8848	22.7774	25.6279	28.3934	31.0325	33.5709	36.1219	38.8045	41.7381	45.0417	48.8344	53.2210	58.1647	63.5502	69.2613	75.1818	81.1954
0	2.7380	5.4680	8.2146	10.9494	13.6868	16.4362	19.2367	22.0502	24.8336	27.5437	30.1371	32.6043	35.0497	37.6022	40.3904	43.5433	47.1895	51.4563	56.3756	61.8275	67.6787	73.7957	80.0451
0	2.6039	5.2026	7.8067	10.4113	13.0149	15.6201	18.2834	20.9820	23.6723	26.3110	28.8546	31.2645	33.5953	35.9872	38.5838	41.5286	44.9652	49.0370	53.8629	59.3710	65.4010	71.7920	78.3830
0	2.4194	4.8393	7.2300	9.6743	12.0886	14.5041	16.9659	19.5032	22.0730	24.6316	27.1356	29.5414	31.8232	34.0860	36.4927	39.2066	42.3910	46.2091	50.8238	56.3039	62.4861	69.1722	76.1638
0	2.1678	4.3373	6.4364	8.6768	10.8283	13.0096	15.2232	17.5499	19.9752	22.4530	24.9373	27.3818	29.7404	31.9945	34.2800	36.7869	39.7054	43.2257	47.5377	52.8220	59.0480	65.9787	73.3689
0	1.7728	3.5522	5.3010	7.0467	9.0228	10.9791	13.0463	15.1796	17.4441	19.8273	22.2832	24.7656	27.2284	29.6255	31.9376	34.3206	37.0007	40.2041	44.1569	49.0854	55.1640	62.2266	69.9691
0	1.2633	2.5702	3.8491	5.2103	6.7695	8.7132	10.6215	12.6717	14.8024	17.0521	19.4201	21.8695	24.3633	26.8643	29.3358	31.7601	34.3042	37.2357	40.8235	45.3363	51.0424	58.0418	66.0214
0	0.9317	1.8936	2.8460	3.8086	4.9928	6.4015	8.2969	10.1829	12.1979	14.3115	16.5427	18.8934	21.3397	23.8573	26.4218	29.0088	31.6073	34.3933	37.6800	41.7839	47.0215	53.6907	61.7084
0	0.7416	1.4952	2.2600	3.0090	3.7833	4.7850	6.0054	7.8172	9.6962	11.6825	13.7857	15.9941	18.3234	20.7676	23.3197	25.9724	28.7186	31.5612	34.6913	38.4683	43.2571	49.4230	57.2148
0	0.6195	1.2425	1.8766	2.5090	3.1268	3.7802	4.6340	5.6897	7.3158	9.1907	11.1355	13.2325	15.4395	17.7530	20.1904	22.7747	25.5290	28.4763	31.6479	35.2603	39.7101	45.4016	52.7321
0	0.5320	1.0645	1.6053	2.1492	2.6879	3.2136	3.7848	4.5303	5.4493	6.8501	8.6829	10.5919	12.6708	14.8683	17.1657	19.5954	22.2243	25.1192	28.3469	31.9830	36.2774	41.6419	48.4941
0	0.4656	0.9308	1.4006	1.8745	2.3482	2.8155	3.2727	3.7786	4.4334	5.2500	6.4349	8.1682	10.0443	12.0987	14.2977	16.6231	19.1110	21.8720	25.0180	28.6611	32.9275	38.1096	44.6064
0	0.4155	0.8305	1.2475	1.6675	2.0888	2.5088	2.9219	3.3302	3.7895	4.3760	5.1128	6.1285	7.6996	9.5251	11.5467	13.7503	16.1407	18.7466	21.7275	25.2533	29.4937	34.6370	40.9735
0	0.3747	0.7489	1.1240	1.5011	1.8797	2.2589	2.6355	3.0052	3.3750	3.7956	4.3259	4.9930	5.8768	7.2788	9.0323	11.0232	13.2631	15.7914	18.5905	21.8801	25.9269	30.9976	37.3287
0	0.3416	0.6830	1.0245	1.3669	1.7104	2.0547	2.3990	2.7403	3.0753	3.4158	3.8052	4.2898	4.9005	5.6944	6.9301	8.5942	10.5765	12.9195	15.6063	18.6782	22.4547	27.2940	33.5433
0	0.3136	0.6271	0.9405	1.2542	1.5684	1.8834	2.1993	2.5144	2.8261	3.1323	3.4485	3.8109	4.2569	4.8183	5.5421	6.6553	8.2536	10.2818	12.7495	15.6264	19.1598	23.7282	29.7421
0	0.2905	0.5809	0.8713	1.1614	1.4515	1.7419	2.0331	2.3247	2.6153	2.9030	3.1873	3.4860	3.8284	4.2447	4.7703	5.4581	6.5185	8.1091	10.1921	12.8155	16.3085	20.5887	26.1574
0	0.2704	0.5408	0.8111	1.0810	1.3503	1.6196	1.8895	2.1604	2.4316	2.7013	2.9679	3.2328	3.5155	3.8421	4.2393	4.7462	5.4244	6.5279	8.1714	10.3322	13.5376	17.7162	22.9394
0	0.2531	0.5063	0.7594	1.0121	1.2640	1.5157	1.7675	2.0200	2.2735	2.5269	2.7789	3.0284	3.2796	3.5518	3.8672	4.2512	4.7741	5.5438	6.7375	8.4970	11.1715	15.0510	20.0530
0	0.2384	0.4769	0.7155	0.9535	1.1903	1.4265	1.6630	1.9009	2.1411	2.3826	2.6225	2.8581	3.0870	3.3201	3.5868	3.9177	4.3491	4.9619	5.8640	7.2380	9.5150	12.8867	17.5026
0	0.2254	0.4510	0.6770	0.9022	1.1255	1.3471	1.5689	1.7930	2.0213	2.2540	2.4868	2.7139	2.9301	3.1325	3.3502	3.6333	4.0324	4.5891	5.3228	6.4451	8.4104	11.4221	15.5515
0	0.2147	0.4296	0.6450	0.8598	1.0725	1.2827	1.4927	1.7046	1.9207	2.1430	2.3684	2.5909	2.8040	3.0015	3.1899	3.4256	3.7772	4.3095	5.0112	5.9598	7.7340	10.5228	14.3246
0	0.2081	0.4165	0.6253	0.8337	1.0400	1.2438	1.4465	1.6502	1.8569	2.0685	2.2844	2.5005	2.7119	2.9142	3.1048	3.3223	3.6407	4.1349	4.8295	5.7321	7.4137	10.0690	13.7069
0	0.2067	0.4136	0.6210	0.8279	1.0329	1.2352	1.4363	1.6380	1.8422	2.0508	2.2636	2.4773	2.6878	2.8911	3.0845	3.3003	3.6118	4.0948	4.7833	5.6788	7.3387	9.9657	13.5338];
if u(2)>22.5
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
