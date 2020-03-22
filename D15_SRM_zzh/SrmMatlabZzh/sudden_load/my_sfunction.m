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
thta=[0
0.05
0.1
0.15
0.2
0.25
0.3
0.35
0.4
0.45
0.5
0.55
0.6
0.65
0.7
0.75
0.8
0.85
0.9
0.95
1
1.05
1.1
1.15
1.2
1.25
]'*9;
% Flux=0:0.01:0.14;
Flux=0:0.01:0.3;

i=[0	4.905612615	9.811318717	14.71616944	19.62060018	24.523661	29.42432331	34.32219913	39.21951618	44.120776	49.03923502	53.99031355	58.9797542	64.00902272	69.079566	74.19434557	79.3668462	84.61501902	89.95683136	95.43980587	101.2325586	107.5347146	114.5458987	122.4634323	131.3032552	140.7720593	150.5463546	160.302651	169.7174587	178.4672874	186.2286473
0	4.883177231	9.766205518	14.64885102	19.53087297	24.41125462	29.28911003	34.16395441	39.03702414	43.91101457	48.79447193	53.69837366	58.63222082	63.60475597	68.62471561	73.70143191	78.84982248	84.08785999	89.43354822	94.9262517	100.7225279	107.0189166	114.0119915	121.897281	130.7135405	140.1772526	149.9652611	159.7544102	169.221544	178.0435065	185.8971417
0	4.780323018	9.560485719	14.34025921	19.11942844	23.89695553	28.67167544	33.44278059	38.21216484	42.98335783	47.76171061	52.55412668	57.3725398	62.23347889	67.15364349	72.14973676	77.23858076	82.43714104	87.76239171	93.23779903	98.98895216	105.2226829	112.1480705	119.9741941	128.8174421	138.4199838	148.4295623	158.493921	168.2608029	177.3779511	185.4931089
0	4.528309881	9.056469766	13.58407925	18.11120556	22.63632081	27.15976139	31.68451779	36.2184405	40.77608432	45.37664149	50.04936178	54.81722906	59.6731305	64.60266159	69.5914178	74.63447503	79.7753749	85.07310582	90.58668857	96.40569665	102.7093629	109.6932824	117.5530505	126.4501651	136.2094101	146.4636727	156.8436095	166.9798768	176.503131	185.0440285
0	4.025994278	8.051658885	12.07707262	16.10029886	20.13956495	24.24793573	28.44248966	32.73250564	37.14596712	41.72295156	46.45470154	51.26407596	56.1048667	60.99859244	65.97424147	71.06081256	76.2893596	81.69543915	87.31520442	93.19047849	99.47338401	106.4162095	114.2748807	123.3001717	133.4668975	144.3401721	155.4518931	166.3339582	176.5182651	185.5367113
0	3.274202498	6.547662617	9.821233698	13.0973143	16.52193319	20.20535949	24.15981695	28.39077085	32.89546013	37.56713292	42.23224069	46.86654021	51.60332593	56.51886148	61.58959619	66.78342493	72.06943508	77.46602568	83.0574155	88.93240395	95.2005034	102.1128616	109.97989	119.1122004	129.7044963	141.3446251	153.4224953	165.3279064	176.4506578	186.1805489
0	2.75441049	5.507543263	8.262131573	11.01315967	13.79896092	16.74299627	20.07089303	23.98556899	28.31423095	32.80758645	37.38846469	42.10276676	46.94848691	51.86572099	56.83934528	61.92037525	67.16463441	72.62740033	78.34981365	84.35793968	90.6772003	97.43872039	105.0833974	114.1085804	124.9921668	137.5934338	151.0396423	164.4157206	176.8065971	187.2972005
0	2.392665428	4.784260822	7.175304792	9.567375424	11.96444127	14.41711334	17.01950047	20.05649938	23.79013569	28.04122078	32.53435341	37.14945329	41.89865658	46.78268407	51.78226698	56.90658867	62.20861237	67.74479134	73.5699241	79.71467305	86.19143437	93.02158706	100.5269796	109.3852403	120.2945891	133.5990801	148.3255523	163.1946802	176.9271382	188.2436008
0	2.128699402	4.25655862	6.383030755	8.509841379	10.63815183	12.7818007	14.97692692	17.3142784	20.10098601	23.59470663	27.67093893	32.1212823	36.81198408	41.69010695	46.6993169	51.77374301	56.93948316	62.36084113	68.21335681	74.64710289	81.56048843	88.70842033	95.97903365	104.195456	114.5767941	128.2415601	144.5899984	161.5941231	177.1825603	189.2839357
0	1.903474726	3.8064013	5.707736603	7.608019367	9.509123353	11.41609228	13.34533165	15.31934484	17.44056746	20.01116875	23.27947637	27.15949807	31.48339707	36.12974192	41.04883795	46.18370841	51.44920827	56.8606465	62.62322822	68.96230702	76.03332008	83.54583422	91.0354173	98.63719825	108.0707148	121.3134709	139.1926699	158.9575817	177.1638373	190.3670676
0	1.715085099	3.429754631	5.142754677	6.854599842	8.566126923	10.27821221	11.99757397	13.74540545	15.54620799	17.51035036	19.89410917	22.91698325	26.56914776	30.77629595	35.46466953	40.56179531	45.9583862	51.43936323	56.98269708	62.96441499	69.80428097	77.70486349	85.92843487	93.56276294	101.7141225	113.6132368	132.2370207	155.4445917	177.25166	191.5804746
0	1.55395663	3.107627346	4.659738465	6.210258966	7.759599527	9.307555277	10.85410257	12.41398146	14.01483852	15.68671612	17.53418739	19.7576309	22.54503885	25.98436251	30.13021605	34.96777543	40.22759539	45.64975521	51.21416064	57.07234272	63.62996008	71.32413572	80.12970036	88.86635663	96.83329717	107.3377735	125.1665753	150.8156359	176.1895812	192.1697828
0	1.426210593	2.852180525	4.277084043	5.700153441	7.120835113	8.539092641	9.956494356	11.37770578	12.8196151	14.30246054	15.85100008	17.57579649	19.66420321	22.29418923	25.56940318	29.56528201	34.31138696	39.59069317	45.1656352	51.10979237	57.63277896	65.03551676	73.61622099	83.06981434	92.3344048	102.4844818	118.7354214	144.4892784	172.2949004	191.46738
0	1.326169654	2.652146139	3.976953112	5.299905274	6.621062519	7.940382839	9.256745408	10.56875042	11.88576159	13.22994384	14.62420756	16.09953761	17.75997307	19.74837863	22.20769915	25.2793114	29.10404403	33.7864926	39.15792522	44.99077771	51.47090013	58.85509484	67.2086366	76.55088228	86.67404623	97.5713116	112.957328	137.9585887	167.5472133	190.2129981
0	1.245784094	2.491415413	3.735814089	4.978055363	6.21874113	7.458474407	8.695823227	9.926493528	11.15024295	12.38726812	13.66387877	15.0063857	16.4514397	18.07648294	19.96901523	22.24054882	25.10308387	28.79490279	33.52164653	39.17683334	45.55241437	52.86583291	61.21341052	70.29804916	80.09491706	91.67621533	107.279214	131.4194485	161.9697505	188.1067234
0	1.175945347	2.351773361	3.526316037	4.697996318	5.868057214	7.037911973	8.207439283	9.370947462	10.52205621	11.67088248	12.84609491	14.07734972	15.39433485	16.82937365	18.41936217	20.20171403	22.28071135	24.95511054	28.55882583	33.39724215	39.45034621	46.56500629	54.92482901	64.16960679	73.43306238	84.02408648	100.194257	124.645582	155.8322317	185.2864069
0	1.106739357	2.213360106	3.318861002	4.420623869	5.52028473	6.619966832	7.721284125	8.819666918	9.906427479	10.97814934	12.05919766	13.18293412	14.38272499	15.69111278	17.12308505	18.67681421	20.35042697	22.27002464	24.844543	28.52077316	33.70288761	40.32383019	48.19086142	57.51359888	67.28785961	76.57572123	91.25910072	117.4095418	149.2248987	181.1508979
0	1.040240764	2.080304981	3.119668521	4.155047183	5.187519809	6.219088836	7.251735939	8.284763257	9.312176332	10.32757351	11.33831197	12.37360342	13.46460271	14.64246468	15.93607958	17.35204879	18.88430405	20.52926413	22.46623067	25.17329881	29.1561449	34.84388231	42.15114289	50.87563928	60.83247664	71.38744754	84.90706626	110.3692352	143.0481181	176.3682789
0	0.982989851	1.965740498	2.948113723	3.927502223	4.903656097	5.877252245	6.848967688	7.81948536	8.789526193	9.759826136	10.73225904	11.71851692	12.73531102	13.79939304	14.92751464	16.14289924	17.49996619	19.06252256	20.89966763	23.22281431	26.39819541	30.79987934	36.81653487	44.80615123	54.05287438	64.61687152	78.86303109	103.3706808	136.7089247	171.010284
0	0.936935327	1.873611442	2.809977725	3.744392258	4.675844977	5.603860915	6.527967737	7.447837106	8.366657252	9.291250528	10.22859804	11.18453347	12.16261389	13.166128	14.19836447	15.2629507	16.40712769	17.76429255	19.47794689	21.69352688	24.57389172	28.29112583	33.05708916	39.65229484	48.44155022	57.20810843	71.18872404	96.7569282	130.2981149	165.315331
0	0.8998855	1.799512671	2.698803703	3.596774043	4.492217345	5.383974462	6.270887075	7.151807424	8.028843727	8.911946429	9.812222808	10.73942481	11.69312201	12.66825459	13.65973942	14.66249341	15.68133678	16.83689381	18.32482412	20.34198369	23.05399863	26.5460027	30.89145263	36.43650555	44.05792072	52.52232437	64.50421631	90.62816373	124.4092878	160.4062669
0	0.866861592	1.733445839	2.599727742	3.464775257	4.327390718	5.186452626	6.040842414	6.889441516	7.732551888	8.578922095	9.440410261	10.32873514	11.24868538	12.19519656	13.16245268	14.14463771	15.13603284	16.18631562	17.49308008	19.27834316	21.75731945	25.06832829	29.30109618	34.57480025	41.19583606	49.22573074	60.00448648	84.64825025	118.9698232	155.3711694
0	0.833495067	1.666676653	2.499646843	3.331256994	4.160156633	4.98563001	5.807005229	6.623610397	7.435074265	8.246875659	9.069806789	9.914852861	10.79135324	11.69977666	12.63761653	13.60236412	14.59151066	15.61136323	16.8035972	18.41589173	20.69819473	23.8444555	27.94589203	33.08452079	39.37223359	46.99718436	57.14802794	79.59374863	114.0499123	150.6109724
0	0.801266598	1.602185025	2.402986206	3.20235277	3.998553382	4.791270656	5.580353497	6.36565081	7.147022916	7.92714415	8.715172728	9.521176928	10.35511621	11.22320174	12.12703722	13.06794338	14.047241	15.06626336	16.18435628	17.6526305	19.76176582	22.77446064	26.80540022	31.9185173	38.07163239	45.25864607	55.55673094	76.97394421	110.6060792	146.7757079
0	0.775133141	1.549731223	2.324512159	3.09766641	3.866168437	4.630606547	5.392212126	6.152216559	6.911851233	7.672762531	8.438954113	9.215260871	10.00651864	10.81949432	11.66849265	12.56965737	13.53913217	14.59306077	15.75907699	17.21402208	19.23898503	22.10850152	26.00741734	31.06681126	37.2162941	44.11151657	54.38330502	75.72890129	109.1330324	144.9334372
0	0.76790121	1.535261248	2.302836444	3.068774965	3.829737392	4.586445597	5.340432946	6.093232803	6.846378532	7.601600372	8.362101136	9.131750592	9.914421804	10.71581044	11.55171839	12.44143058	13.40423518	14.45942038	15.63260586	17.07998436	19.08046955	21.91182931	25.77509919	30.81722154	36.96661944	43.75936143	53.98419049	75.35271108	108.7453777	144.549226
];
if u(2)>=22.5/2
    beta=22.5-u(2);
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
