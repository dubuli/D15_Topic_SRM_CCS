%%%%x=textread('l23.txt','%s');
num=500;
fileID=fopen('l15.txt');
x=textscan(fileID,'%s');
y=hex2dec(x{1})';
y=y/229;
%y=[31,0,32,0,46,0,57,0,75,0,86,0,92,0,107,0,120,0,128,0,148,0,166,0,169,0,179,0,194,0,202,0,218,0,229,0,245,0,2,1,16,1,20,1,32,1,52,1,62,1,81,1,86,1,93,1,104,1,124,1,130,1,148,1,159,1,169,1,175,1,199,1,210,1,230,1,230,1,239,1,251,1,11,2,23,2,40,2,53,2,60,2,71,2,81,2,93,2,112,2,122,2,128,2,138,2,153,2,171,2,183,2,189,2,199,2,219,2,229,2,237,2,252,2,8,3,13,3,18,3,40,3,51,3,69,3,76,3,89,3,96,3,107,3,120,3,134,3,142,3,159,3,172,3,184,3,191,3,203,3,217,3,4,4,244,3,250,3,0,4,18,4,28,4,40,4,55,4,62,4,66,4,84,4,97,4,112,4,122,4,132,4,139,4,151,4,178,4,182,4,193,4,198,4,208,4,218,4,229,4,252,4,255,4,10,5,19,5,29,5,44,5,59,5,67,5,78,5,84,5,109,5,108,5,124,5,140,5,142,5,151,5,162,5,175,5,187,5,198,5,211,5,222,5,233,5,240,5,255,5,7,6,21,6,12,6,43,6,47,6,65,6,75,6,87,6,91,6,108,6,111,6,126,6,136,6,150,6,164,6,171,6,182,6,191,6,204,6,206,6,231,6,239,6,243,6,254,6,7,7,18,7,35,7,42,7,50,7,68,7,73,7,87,7,101,7,105,7,110,7,123,7,140,7,146,7,161,7,173,7,180,7,186,7,200,7,210,7,226,7,230,7,238,7,247,7,253,7,13,8,29,8,38,8,48,8,51,8,62,8,81,8,86,8,100,8,103,8,117,8,126,8,135,8,148,8,161,8,172,8,178,8,182,8,191,8,207,8,215,8];
%y=[0.135371179039301,0,0.139737991266376,0,0.200873362445415,0,0.248908296943231,0,0.327510917030568,0,0.375545851528384,0,0.401746724890830,0,0.467248908296943,0,0.524017467248908,0,0.558951965065502,0,0.646288209606987,0,0.724890829694323,0,0.737991266375546,0,0.781659388646288,0,0.847161572052402,0,0.882096069868996,0,0.951965065502183,0,1,0,1.06986899563319,0,0.00873362445414847,0.00436681222707424,0.0698689956331878,0.00436681222707424,0.0873362445414847,0.00436681222707424,0.139737991266376,0.00436681222707424,0.227074235807860,0.00436681222707424,0.270742358078603,0.00436681222707424,0.353711790393013,0.00436681222707424,0.375545851528384,0.00436681222707424,0.406113537117904,0.00436681222707424,0.454148471615721,0.00436681222707424,0.541484716157205,0.00436681222707424,0.567685589519651,0.00436681222707424,0.646288209606987,0.00436681222707424,0.694323144104803,0.00436681222707424,0.737991266375546,0.00436681222707424,0.764192139737991,0.00436681222707424,0.868995633187773,0.00436681222707424,0.917030567685590,0.00436681222707424,1.00436681222707,0.00436681222707424,1.00436681222707,0.00436681222707424,1.04366812227074,0.00436681222707424,1.09606986899563,0.00436681222707424,0.0480349344978166,0.00873362445414847,0.100436681222707,0.00873362445414847,0.174672489082969,0.00873362445414847,0.231441048034935,0.00873362445414847,0.262008733624454,0.00873362445414847,0.310043668122271,0.00873362445414847,0.353711790393013,0.00873362445414847,0.406113537117904,0.00873362445414847,0.489082969432314,0.00873362445414847,0.532751091703057,0.00873362445414847,0.558951965065502,0.00873362445414847,0.602620087336245,0.00873362445414847,0.668122270742358,0.00873362445414847,0.746724890829694,0.00873362445414847,0.799126637554585,0.00873362445414847,0.825327510917031,0.00873362445414847,0.868995633187773,0.00873362445414847,0.956331877729258,0.00873362445414847,1,0.00873362445414847,1.03493449781659,0.00873362445414847,1.10043668122271,0.00873362445414847,0.0349344978165939,0.0131004366812227,0.0567685589519651,0.0131004366812227,0.0786026200873363,0.0131004366812227,0.174672489082969,0.0131004366812227,0.222707423580786,0.0131004366812227,0.301310043668122,0.0131004366812227,0.331877729257642,0.0131004366812227,0.388646288209607,0.0131004366812227,0.419213973799127,0.0131004366812227,0.467248908296943,0.0131004366812227,0.524017467248908,0.0131004366812227,0.585152838427948,0.0131004366812227,0.620087336244542,0.0131004366812227,0.694323144104803,0.0131004366812227,0.751091703056769,0.0131004366812227,0.803493449781659,0.0131004366812227,0.834061135371179,0.0131004366812227,0.886462882096070,0.0131004366812227,0.947598253275109,0.0131004366812227,0.0174672489082969,0.0174672489082969,1.06550218340611,0.0131004366812227,1.09170305676856,0.0131004366812227,0,0.0174672489082969,0.0786026200873363,0.0174672489082969,0.122270742358079,0.0174672489082969,0.174672489082969,0.0174672489082969,0.240174672489083,0.0174672489082969,0.270742358078603,0.0174672489082969,0.288209606986900,0.0174672489082969,0.366812227074236,0.0174672489082969,0.423580786026201,0.0174672489082969,0.489082969432314,0.0174672489082969,0.532751091703057,0.0174672489082969,0.576419213973799,0.0174672489082969,0.606986899563319,0.0174672489082969,0.659388646288210,0.0174672489082969,0.777292576419214,0.0174672489082969,0.794759825327511,0.0174672489082969,0.842794759825328,0.0174672489082969,0.864628820960699,0.0174672489082969,0.908296943231441,0.0174672489082969,0.951965065502183,0.0174672489082969,1,0.0174672489082969,1.10043668122271,0.0174672489082969,1.11353711790393,0.0174672489082969,0.0436681222707424,0.0218340611353712,0.0829694323144105,0.0218340611353712,0.126637554585153,0.0218340611353712,0.192139737991266,0.0218340611353712,0.257641921397380,0.0218340611353712,0.292576419213974,0.0218340611353712,0.340611353711790,0.0218340611353712,0.366812227074236,0.0218340611353712,0.475982532751092,0.0218340611353712,0.471615720524017,0.0218340611353712,0.541484716157205,0.0218340611353712,0.611353711790393,0.0218340611353712,0.620087336244542,0.0218340611353712,0.659388646288210,0.0218340611353712,0.707423580786026,0.0218340611353712,0.764192139737991,0.0218340611353712,0.816593886462882,0.0218340611353712,0.864628820960699,0.0218340611353712,0.921397379912664,0.0218340611353712,0.969432314410480,0.0218340611353712,1.01746724890830,0.0218340611353712,1.04803493449782,0.0218340611353712,1.11353711790393,0.0218340611353712,0.0305676855895197,0.0262008733624454,0.0917030567685590,0.0262008733624454,0.0524017467248908,0.0262008733624454,0.187772925764192,0.0262008733624454,0.205240174672489,0.0262008733624454,0.283842794759825,0.0262008733624454,0.327510917030568,0.0262008733624454,0.379912663755459,0.0262008733624454,0.397379912663755,0.0262008733624454,0.471615720524017,0.0262008733624454,0.484716157205240,0.0262008733624454,0.550218340611354,0.0262008733624454,0.593886462882096,0.0262008733624454,0.655021834061135,0.0262008733624454,0.716157205240175,0.0262008733624454,0.746724890829694,0.0262008733624454,0.794759825327511,0.0262008733624454,0.834061135371179,0.0262008733624454,0.890829694323144,0.0262008733624454,0.899563318777293,0.0262008733624454,1.00873362445415,0.0262008733624454,1.04366812227074,0.0262008733624454,1.06113537117904,0.0262008733624454,1.10917030567686,0.0262008733624454,0.0305676855895197,0.0305676855895197,0.0786026200873363,0.0305676855895197,0.152838427947598,0.0305676855895197,0.183406113537118,0.0305676855895197,0.218340611353712,0.0305676855895197,0.296943231441048,0.0305676855895197,0.318777292576419,0.0305676855895197,0.379912663755459,0.0305676855895197,0.441048034934498,0.0305676855895197,0.458515283842795,0.0305676855895197,0.480349344978166,0.0305676855895197,0.537117903930131,0.0305676855895197,0.611353711790393,0.0305676855895197,0.637554585152839,0.0305676855895197,0.703056768558952,0.0305676855895197,0.755458515283843,0.0305676855895197,0.786026200873362,0.0305676855895197,0.812227074235808,0.0305676855895197,0.873362445414847,0.0305676855895197,0.917030567685590,0.0305676855895197,0.986899563318777,0.0305676855895197,1.00436681222707,0.0305676855895197,1.03930131004367,0.0305676855895197,1.07860262008734,0.0305676855895197,1.10480349344978,0.0305676855895197,0.0567685589519651,0.0349344978165939,0.126637554585153,0.0349344978165939,0.165938864628821,0.0349344978165939,0.209606986899563,0.0349344978165939,0.222707423580786,0.0349344978165939,0.270742358078603,0.0349344978165939,0.353711790393013,0.0349344978165939,0.375545851528384,0.0349344978165939,0.436681222707424,0.0349344978165939,0.449781659388646,0.0349344978165939,0.510917030567686,0.0349344978165939,0.550218340611354,0.0349344978165939,0.589519650655022,0.0349344978165939,0.646288209606987,0.0349344978165939,0.703056768558952,0.0349344978165939,0.751091703056769,0.0349344978165939,0.777292576419214,0.0349344978165939,0.794759825327511,0.0349344978165939,0.834061135371179,0.0349344978165939,0.903930131004367,0.0349344978165939,0.938864628820961,0.0349344978165939];
z=zeros(1,num);
for i=1:num
    z(i)=y(2*i-1)+y(2*i)*256;%����
end


%flux=0.0018:0.0018:0.0018*200;
flux=zeros(1,num);
for i=2:num
    flux(i)=flux(i-1)+(107-z(i-1)*1)/50000;
end
plot(z,flux)



a=[0	0.029676865	0.059353747	0.089030664	0.118707632	0.148384668	0.17806179	0.207739015	0.23741636	0.296775481	0.415511315	0.5937088	0.890665901	1.471625459	2.033997591
0	0.029686387	0.059372808	0.089059298	0.118745891	0.148432622	0.178119524	0.207806633	0.237494031	0.296870694	0.415644936	0.593900205	0.890948547	1.471997202	2.034206216
0	0.029709323	0.05941868	0.089128107	0.118837636	0.148547304	0.178257144	0.207967192	0.237677532	0.297100086	0.415966259	0.594359514	0.891633802	1.472994616	2.034754209
0	0.029750943	0.059501921	0.089252968	0.119004119	0.148755409	0.178506873	0.208258546	0.238010518	0.297516351	0.416549349	0.595192984	0.892876587	1.474692599	2.035682382
0	0.029805064	0.059610163	0.089415333	0.119220607	0.149026021	0.178831611	0.208637411	0.23844352	0.298057647	0.41730758	0.59627677	0.894491709	1.476911812	2.036931371
0	0.029875171	0.059750378	0.089625655	0.119501039	0.149376564	0.179252266	0.209128183	0.239004418	0.298758827	0.418289768	0.597680653	0.896582214	1.479773389	2.038562824
0	0.029958528	0.059917091	0.089875726	0.119834469	0.149793355	0.179752421	0.209711705	0.23967132	0.299592521	0.419457581	0.599349859	0.899069473	1.483197714	2.040516925
0	0.03005587	0.060111776	0.090167755	0.120223843	0.150280077	0.180336493	0.210393132	0.240450118	0.300566096	0.420821351	0.601299126	0.901969925	1.487151881	2.04275096
0	0.030172993	0.060346024	0.090519128	0.120692344	0.150865708	0.181039258	0.211213037	0.241387181	0.301737523	0.422462292	0.603644561	0.905457603	1.49182874	2.045344613
0	0.030302457	0.060604953	0.090907524	0.121210208	0.151513044	0.181816069	0.212119332	0.242422978	0.303032378	0.424276145	0.606237129	0.909309907	1.497053971	2.048229926
0	0.030452004	0.060904047	0.091356167	0.121808404	0.152260795	0.182713381	0.213166214	0.243619451	0.304528104	0.426371392	0.60923185	0.91374998	1.502959695	2.051480161
0	0.030615809	0.061231657	0.091847585	0.122463631	0.153079837	0.183696242	0.214312908	0.24493	0.306166443	0.428666441	0.61251206	0.918603513	1.509416718	2.055023744
0	0.030803835	0.061607712	0.09241167	0.123215751	0.154019995	0.184824445	0.215629172	0.246434351	0.30804707	0.431300945	0.616277279	0.924155886	1.516580969	2.058886885
0	0.031012295	0.062024632	0.093037053	0.124049601	0.155062319	0.18607525	0.217088477	0.248102186	0.310132085	0.434221837	0.620451571	0.930293366	1.524333773	2.063004753
0	0.031246345	0.062492733	0.093739209	0.124985816	0.156232599	0.187479606	0.218726932	0.249974775	0.312473092	0.437501429	0.625138089	0.937147513	1.532751627	2.067377993
0	0.031502245	0.063004536	0.094506919	0.126009438	0.157512139	0.189015077	0.220518361	0.252022202	0.315032694	0.441087339	0.630261847	0.944607005	1.541747185	2.071974517
0	0.031777958	0.063555963	0.095334064	0.127112308	0.158890742	0.190669428	0.222448487	0.254228153	0.31779049	0.444950996	0.635781556	0.952610499	1.551305537	2.076797172
0	0.032078462	0.064156973	0.096235585	0.128314345	0.160393306	0.192472539	0.224552172	0.256632472	0.320796311	0.449162217	0.641796477	0.961287516	1.561449553	2.081860688
0	0.032407448	0.064814948	0.097222554	0.129630316	0.162038289	0.194446563	0.226855272	0.25926472	0.32408713	0.453772782	0.648378377	0.970644769	1.57201742	2.087106134
0	0.032769768	0.065539592	0.098309527	0.131079628	0.163849953	0.196620613	0.229391751	0.262163714	0.327711473	0.45885076	0.655624228	0.980856871	1.583137852	2.09254415
0	0.033160319	0.066320697	0.099481192	0.132641865	0.165802777	0.19896407	0.232125887	0.26528863	0.331618302	0.464324608	0.663427981	0.9917424	1.594688413	2.098142907
0	0.033585346	0.067170754	0.100756289	0.134342012	0.167927997	0.201514414	0.235101417	0.268689455	0.335870142	0.47028186	0.671906921	1.003381295	1.606741732	2.103920096
0	0.034040492	0.068081051	0.102121745	0.136162641	0.170203828	0.204245504	0.238287844	0.272331343	0.34042343	0.476661494	0.680968197	1.01571084	1.619217828	2.109839532
0	0.034546156	0.069092384	0.103638758	0.138185351	0.172732279	0.207279766	0.241828024	0.276377581	0.345482329	0.483749301	0.690989445	1.028950203	1.632167653	2.115906807
0	0.035104931	0.07020994	0.105315108	0.140420515	0.17552632	0.210632769	0.245740134	0.280848944	0.35107288	0.491581337	0.702004755	1.043111675	1.645454548	2.122095486
0	0.035728214	0.071456515	0.107184991	0.142913731	0.178642959	0.214372943	0.250104041	0.285836721	0.35730928	0.500316414	0.714160138	1.05819401	1.659061494	2.128414828
0	0.036425612	0.072851322	0.109277226	0.145703435	0.182130263	0.218557995	0.25498707	0.291417876	0.364287743	0.510083616	0.727439291	1.074116888	1.672923417	2.13484216
0	0.037188312	0.074376733	0.111565373	0.148754381	0.185944158	0.223135049	0.260327509	0.297521914	0.371920201	0.520753038	0.741659992	1.090782977	1.686973094	2.14136176
0	0.038030122	0.076060368	0.114090861	0.152121821	0.190153747	0.228187044	0.266222143	0.304259429	0.380344867	0.53250153	0.756919608	1.108147996	1.701227848	2.148005092
0	0.038973492	0.077947127	0.116921048	0.155895622	0.194871413	0.233848843	0.272828325	0.311810252	0.389786195	0.545561035	0.773051116	1.125924771	1.715511104	2.154720298
0	0.04008148	0.080163131	0.120245136	0.160328101	0.200412682	0.240499155	0.280587898	0.320679328	0.400871503	0.560577262	0.79052079	1.144328841	1.729802642	2.161526949
0	0.041364025	0.082728258	0.124092987	0.165459161	0.206827411	0.248197745	0.289570542	0.330945642	0.413679081	0.577116305	0.808916589	1.163130087	1.74402954	2.168406534
0	0.042842323	0.085684907	0.128528288	0.171373758	0.214221711	0.257071958	0.299924386	0.342775927	0.428345597	0.594908137	0.828174317	1.182567137	1.758245362	2.175366737
0	0.044542948	0.089086236	0.133630881	0.178178476	0.222728771	0.267281358	0.311833379	0.356360177	0.44484158	0.613644352	0.848042326	1.202347318	1.772366151	2.182386667
0	0.046562701	0.093125891	0.139691479	0.186260836	0.232832957	0.279405409	0.325953781	0.372353585	0.463226535	0.633341073	0.868506547	1.222475985	1.786426744	2.189476151
0	0.048998761	0.097998396	0.147002161	0.196010172	0.245019638	0.294009313	0.342807863	0.390915084	0.482860664	0.653911704	0.889305976	1.242811753	1.800403444	2.196632449
0	0.052041109	0.104084129	0.156133604	0.208186723	0.260222005	0.31200258	0.36271741	0.411479895	0.503654643	0.675233832	0.910459881	1.26339207	1.814263759	2.203853266
0	0.055724603	0.111453246	0.167190714	0.222919713	0.27840897	0.332519365	0.384058334	0.432745814	0.525362807	0.697129176	0.932097319	1.284276855	1.828039178	2.211124945
0	0.060012596	0.120033099	0.180063197	0.240015609	0.298852933	0.354253704	0.405597451	0.454658162	0.547410216	0.719110667	0.953964451	1.305271887	1.841673462	2.218414523
0	0.064359398	0.12873112	0.193113836	0.257332397	0.319441749	0.376048917	0.428064435	0.477391805	0.570197997	0.741332457	0.976005902	1.326509115	1.85523202	2.225749562
0	0.068411215	0.136839259	0.205280803	0.273525386	0.339179429	0.397716574	0.450574189	0.49994721	0.592838136	0.763605902	0.997943339	1.347720843	1.868616873	2.233084817
0	0.073092635	0.146209002	0.219336334	0.292046492	0.360580385	0.420213073	0.473082539	0.522492299	0.615285806	0.78618533	1.020118577	1.368955996	1.881898001	2.240449155
0	0.078090229	0.156212811	0.234339387	0.311682116	0.382635635	0.442636841	0.495431578	0.544937808	0.637784467	0.808947084	1.042398905	1.390139852	1.89505726	2.247837536
0	0.082967214	0.165975819	0.24898405	0.330844507	0.404180698	0.46457347	0.517647457	0.56726946	0.660333318	0.831802315	1.064739768	1.411329327	1.908100692	2.255245798
0	0.087731171	0.175513162	0.263290916	0.349552304	0.42515088	0.486240946	0.539910719	0.589741724	0.683095607	0.854716913	1.08732304	1.432531402	1.921027766	2.262649745
0	0.092178878	0.184417496	0.276649988	0.367083776	0.445278529	0.50775116	0.562215733	0.612357979	0.706125697	0.877734819	1.109909113	1.453684633	1.933863342	2.270066066
0	0.096497449	0.193063632	0.289624166	0.384197805	0.465331177	0.52950316	0.584814697	0.635323419	0.729347957	0.900639883	1.132535185	1.474747724	1.946570048	2.277481541
0	0.101020408	0.202120013	0.303217427	0.402155924	0.486409422	0.552166593	0.608025453	0.65867657	0.752755632	0.923688415	1.155234854	1.495770264	1.959140101	2.284915831
0	0.105843723	0.211779287	0.317709981	0.421188866	0.50835238	0.57535703	0.631464755	0.682082851	0.776183223	0.946874269	1.178020955	1.516659529	1.971573561	2.292363967
0	0.111203043	0.222513984	0.33380101	0.441910015	0.531328879	0.598939601	0.654717614	0.705277456	0.799399989	0.970027276	1.200710472	1.537327427	1.983800855	2.299788746
0	0.116182082	0.232487486	0.348783421	0.461682535	0.553575536	0.622003747	0.677935153	0.728660975	0.822934917	0.993440617	1.223438222	1.557883634	1.995899531	2.307244148
0	0.120200888	0.240536871	0.360885207	0.478172639	0.574034063	0.644432314	0.701053282	0.752040602	0.846420796	1.016693152	1.245977332	1.578119662	2.007766254	2.314651526
0	0.124567075	0.249282461	0.374022252	0.495613263	0.594761484	0.666953943	0.724496445	0.775722124	0.870031848	1.040078882	1.268734108	1.598249207	2.019539471	2.322081188
0	0.129332888	0.258830188	0.38836106	0.514397385	0.616173331	0.689573201	0.74773069	0.7991504	0.893434657	1.063468035	1.291563984	1.618144182	2.031136437	2.329499441
0	0.134050096	0.268281558	0.402561206	0.533030315	0.637432703	0.711998296	0.770762774	0.822383803	0.916795046	1.086836032	1.314450341	1.637857116	2.04258256	2.336900678
0	0.138645143	0.27748883	0.416401309	0.551217575	0.658309484	0.734145526	0.793648644	0.845578342	0.940239528	1.110228033	1.337407682	1.657454374	2.053866544	2.344288314
0	0.142940937	0.286096594	0.42934928	0.568376652	0.678480541	0.755942234	0.816420343	0.868792712	0.963865952	1.133697576	1.36029899	1.676907339	2.064984027	2.351658376
0	0.147227321	0.294686332	0.442273402	0.585479326	0.698558572	0.777706073	0.839210747	0.89213346	0.987545726	1.157077785	1.383025326	1.696237397	2.0759553	2.359010975
0	0.151687552	0.303625886	0.455727047	0.603275875	0.719384837	0.800117163	0.862530811	0.915890505	1.011348646	1.18052818	1.405754426	1.71543214	2.086767634	2.366341587
0	0.156440605	0.313154264	0.470066579	0.622102227	0.741085509	0.823208889	0.886336403	0.939838543	1.035161617	1.204088357	1.428536443	1.734525725	2.097446643	2.373668438
0	0.161817327	0.323936084	0.486272528	0.642830336	0.76376668	0.846486096	0.910019673	0.963413853	1.05873826	1.227425536	1.451099257	1.753399168	2.107929981	2.380953257
0	0.166945907	0.334221811	0.501767213	0.663031984	0.785980707	0.869289467	0.933096935	0.986866295	1.082379126	1.250838153	1.473468105	1.772007342	2.118271935	2.388220686
0	0.171019325	0.342390595	0.514094449	0.679828925	0.806536986	0.891518802	0.95614101	1.010403746	1.106036162	1.274245854	1.49566336	1.790110038	2.128422664	2.395440754
0	0.175283766	0.35094388	0.526988302	0.697030551	0.827155496	0.913824898	0.979489183	1.03412516	1.12979179	1.297688366	1.517782368	1.807748159	2.138437252	2.402652272
0	0.180037248	0.360481596	0.541356125	0.715820716	0.848495098	0.936316914	1.002707066	1.057630629	1.15332441	1.32100257	1.539716149	1.824848643	2.148284137	2.409835662
0	0.184810081	0.370060568	0.555787358	0.734678227	0.869771557	0.958597862	1.025615877	1.080886162	1.176742153	1.344276971	1.561554385	1.841394253	2.157950489	2.416992102
0	0.189401727	0.379277986	0.569678685	0.752925281	0.890608874	0.98057475	1.048283596	1.104051864	1.20015985	1.367541888	1.583177258	1.857446073	2.167429692	2.424109807
0	0.193725953	0.3879605	0.582768723	0.770272127	0.910890328	1.002260337	1.070858246	1.127201444	1.223557365	1.390783686	1.604473148	1.873078049	2.17672916	2.43119641
0	0.197953971	0.396452194	0.595569977	0.78722711	0.930838838	1.023732144	1.093317054	1.150294057	1.246927191	1.413999502	1.625479095	1.888384163	2.185859158	2.438256244
0	0.202308916	0.405202605	0.608758603	0.804643361	0.951151864	1.045564387	1.116038253	1.17358317	1.27050409	1.437219278	1.646256987	1.903383223	2.19480266	2.445286695
0	0.206878162	0.414388235	0.622598511	0.822804059	0.972054401	1.067858378	1.139083665	1.197105374	1.294179115	1.460363003	1.666760918	1.918120474	2.203596602	2.452305937
0	0.212020425	0.424732924	0.638163069	0.842836379	0.994101234	1.090579497	1.162322945	1.220533396	1.317511998	1.483101907	1.68685781	1.932488779	2.212158972	2.459244325
0	0.216888321	0.434529054	0.652918062	0.862141235	1.015733459	1.112964035	1.185230778	1.243716206	1.340849517	1.505884019	1.706845272	1.946645606	2.22059041	2.466165439
0	0.220931379	0.442665836	0.66519252	0.878717544	1.035833895	1.134781389	1.207875211	1.266804694	1.364329828	1.528598074	1.726570169	1.9605143	2.228825913	2.473006565
0	0.225130788	0.451120686	0.677935882	0.895643161	1.05590528	1.156532549	1.230560108	1.29002469	1.387915786	1.55108782	1.746159443	1.974191702	2.236918876	2.479801617
0	0.229816685	0.460561196	0.692150741	0.914154003	1.076786522	1.178546009	1.25317834	1.313090281	1.41128974	1.573195755	1.765542428	1.987678688	2.24487462	2.486530186
0	0.234556809	0.470115674	0.706534064	0.932873363	1.097746669	1.200436616	1.275598341	1.335934012	1.434357027	1.594910637	1.784724147	2.000939995	2.252696648	2.493182843
0	0.239083421	0.479243164	0.720278397	0.950906134	1.118293782	1.222035187	1.297815359	1.358625543	1.457254218	1.616287768	1.803576209	2.01393557	2.260390663	2.499758701
0	0.243377341	0.487904326	0.733323417	0.968163057	1.138328088	1.243349206	1.319884749	1.381214164	1.480016776	1.637343168	1.821878008	2.026657169	2.267945628	2.50625177
0	0.247495094	0.496212474	0.745839593	0.984796891	1.157977527	1.264456949	1.341904113	1.403784474	1.502608998	1.658098505	1.839520904	2.039121981	2.275396496	2.512678586
0	0.25174844	0.504797882	0.758770242	1.00192323	1.17801367	1.285903433	1.364155724	1.426472484	1.525179494	1.678578141	1.856467895	2.051287933	2.282734376	2.519021024
0	0.256345256	0.514081892	0.772742831	1.020223322	1.198884569	1.307982074	1.386825568	1.449384503	1.547687254	1.698765701	1.872790427	2.063163363	2.289988236	2.52530954
0	0.261516441	0.524533518	0.78844218	1.040270634	1.220655887	1.33030558	1.409442601	1.472029971	1.569637458	1.718500221	1.888457834	2.074683223	2.297119866	2.531496594
0	0.266493072	0.534595135	0.803571549	1.059805079	1.241966577	1.352174388	1.431552685	1.494013444	1.591234792	1.738071451	1.903710899	2.085956921	2.304179929	2.537626514
0	0.270525255	0.542746638	0.815855671	1.076425865	1.261811286	1.373398519	1.453247209	1.515666368	1.612466803	1.757478239	1.918532975	2.096934572	2.31112885	2.54366196
0	0.274502329	0.550788657	0.827962578	1.092621369	1.281197755	1.394334535	1.474761478	1.537238649	1.633355029	1.776662883	1.932956888	2.107664893	2.31799114	2.5496272
0	0.27898956	0.559868424	0.841611772	1.110418263	1.301267069	1.41541759	1.496024287	1.558469546	1.653706443	1.795527281	1.946967137	2.118152279	2.32477192	2.555531462
0	0.283580194	0.569161767	0.855572992	1.128525013	1.321368234	1.436321262	1.51683955	1.579189664	1.673471321	1.813961089	1.960627329	2.128405584	2.331456013	2.561357652
0	0.287971571	0.578054272	0.86893348	1.145970699	1.34100051	1.456816913	1.537244101	1.59936952	1.692815437	1.831867317	1.97398545	2.138450408	2.338041521	2.567114051
0	0.292150187	0.586518183	0.881653469	1.162685724	1.360126585	1.476827933	1.557213433	1.618993314	1.711801044	1.849084785	1.987045912	2.14827143	2.344512663	2.572786289
0	0.296162284	0.594646871	0.893868404	1.178797657	1.37881718	1.496325073	1.576738282	1.63809936	1.730445333	1.865561413	1.999837126	2.15787457	2.35089581	2.578400412
0	0.300328846	0.603092641	0.90655273	1.195416317	1.397875857	1.515869391	1.596157341	1.656949457	1.748894105	1.88137493	2.01235164	2.167230263	2.357162117	2.583911755
0	0.30479737	0.612155889	0.920152513	1.213027	1.417532927	1.535575944	1.615415498	1.675518796	1.767152559	1.896530495	2.024602329	2.1763706	2.36333974	2.589357077
0	0.309834211	0.622379487	0.93546016	1.23230626	1.437846109	1.555283199	1.634150408	1.693547917	1.784930974	1.910933025	2.036510757	2.185238196	2.369389833	2.59469714
0	0.314780942	0.632424058	0.950505995	1.251330546	1.457626314	1.574385657	1.652064113	1.71086422	1.802207676	1.924797864	2.048143648	2.193890732	2.375346359	2.599947465
0	0.318819582	0.640624708	0.962825605	1.267700365	1.475922783	1.59256806	1.66919425	1.727682977	1.819052855	1.938190284	2.059474988	2.202316529	2.38119694	2.605090424
0	0.322647161	0.648398217	0.97449281	1.283149779	1.493361735	1.609921499	1.685739401	1.74416652	1.835429045	1.951121122	2.070461385	2.210494055	2.386933111	2.610131302
0	0.327041829	0.657329895	0.987872387	1.300266426	1.511078526	1.626914367	1.701809068	1.760210381	1.850988058	1.963523325	2.081043798	2.218396725	2.392550513	2.615075741
0	0.331605261	0.666609595	1.001761447	1.317829184	1.528504015	1.643258729	1.717301333	1.775711928	1.865484848	1.975393315	2.091221078	2.226020347	2.398041956	2.619907349
0	0.33598397	0.675516822	1.015091898	1.334730134	1.545095552	1.658684397	1.73212795	1.790632556	1.878912791	1.986788777	2.101032482	2.233380266	2.403418182	2.624638582
0	0.34015306	0.684000439	1.027784973	1.350862482	1.560810212	1.673188087	1.746292447	1.804943147	1.891389095	1.997713894	2.110486764	2.240468995	2.408669152	2.629248416
0	0.344169556	0.692176029	1.040008962	1.366346434	1.575609863	1.686821438	1.759820662	1.818617881	1.90297625	2.008158698	2.119610876	2.247291695	2.413805671	2.633753511
0	0.348225036	0.700434285	1.052343431	1.381856185	1.589947482	1.699937448	1.772993374	1.83180397	1.913868604	2.018169397	2.128436281	2.25385214	2.418817789	2.638132036
0	0.352438257	0.709017899	1.065144828	1.397762203	1.603980362	1.712678948	1.785897716	1.844452211	1.924173452	2.027770773	2.13696269	2.260157569	2.423701734	2.642397613
0	0.357051493	0.718422842	1.079139822	1.414697859	1.61790891	1.725159801	1.798560617	1.856411899	1.933872333	2.036922402	2.145131365	2.266175744	2.42844187	2.646538341
0	0.361657517	0.727817922	1.093106389	1.431396972	1.631108336	1.737052163	1.810693145	1.867443497	1.94289944	2.045579086	2.152933095	2.271923851	2.433057069	2.650558923
0	0.365545705	0.735750073	1.104913894	1.445767929	1.642742185	1.747881105	1.821993317	1.877419444	1.9512566	2.053720574	2.160364644	2.277428676	2.43755342	2.654460208
0	0.369157756	0.743120174	1.115878077	1.458862565	1.653185029	1.757826987	1.832447564	1.886452499	1.959008311	2.061411304	2.167424446	2.282699502	2.441918208	2.658234684
0	0.373309579	0.751597135	1.12846284	1.473130763	1.663700341	1.767591322	1.842460086	1.894888102	1.966283242	2.068653325	2.174066067	2.287716147	2.446132144	2.661880609
0	0.377642202	0.760447637	1.141585779	1.487444848	1.673886685	1.776990175	1.851841093	1.902712867	1.973076606	2.075393559	2.180230337	2.292462329	2.450173606	2.665388228
0	0.381766108	0.76887362	1.154067777	1.500672203	1.683259479	1.785729996	1.860344483	1.9098336	1.979358367	2.081638562	2.185927244	2.296945098	2.454051977	2.668767743
0	0.385737997	0.776990361	1.166067676	1.51295947	1.691891593	1.793787337	1.867920865	1.916260736	1.985122431	2.087359696	2.191129303	2.301144646	2.457748871	2.671997852
0	0.389456684	0.784589986	1.177273594	1.524115718	1.69970557	1.801121384	1.874586842	1.92201163	1.990381779	2.092562434	2.195867213	2.305049677	2.461266494	2.675090941
0	0.393154261	0.792147544	1.188374605	1.534809678	1.707063799	1.807980493	1.880532297	1.927216413	1.995213196	2.097291554	2.200157916	2.308637715	2.464588697	2.678022938
0	0.396941631	0.799890308	1.199697951	1.545329625	1.714098856	1.814470095	1.885866725	1.931933518	1.999644147	2.101585156	2.204025045	2.311899519	2.46771663	2.680794737
0	0.401031081	0.808253403	1.211868505	1.556114709	1.721005768	1.820708316	1.890705978	1.936222658	2.003708005	2.105458108	2.207458289	2.314828417	2.470641474	2.683395665
0	0.405074259	0.816523615	1.223865955	1.566376116	1.72745708	1.826478206	1.894984238	1.940014367	2.007337451	2.108892325	2.210491739	2.317398219	2.473349049	2.685807763
0	0.40804208	0.822593381	1.232678637	1.573957512	1.732458813	1.831122747	1.898383818	1.943044685	2.010335425	2.111818099	2.213075293	2.319606852	2.475820314	2.688048119
0	0.41005255	0.82670333	1.238646491	1.579021084	1.736002201	1.834507679	1.900869506	1.945269459	2.012660333	2.114205022	2.215192294	2.321446419	2.478029615	2.690107271
0	0.411894048	0.830468206	1.244101532	1.583481656	1.739032627	1.837407227	1.902939324	1.947046613	2.014517261	2.116196129	2.21693654	2.322961283	2.479942456	2.691937906
0	0.413548758	0.833851615	1.24899491	1.587369707	1.74160656	1.83990191	1.904702261	1.948512362	2.015981884	2.117852256	2.218362391	2.324187263	2.481530124	2.693539494
0	0.414660605	0.836123858	1.25228129	1.589961713	1.74337113	1.841691153	1.905985541	1.949583691	2.017010795	2.119109983	2.21948332	2.325140627	2.482787804	2.694932675
0	0.415505276	0.837849339	1.254775777	1.591890599	1.744679291	1.84302277	1.906954722	1.950392826	2.017753168	2.120024637	2.220339482	2.32584931	2.483731303	2.696073074
0	0.416058203	0.83897782	1.256410184	1.593146382	1.745541762	1.843913942	1.907628862	1.95095741	2.018257432	2.120637301	2.220949177	2.326348988	2.484394195	2.696939244
0	0.416364378	0.839602143	1.257315976	1.593837464	1.746022493	1.844412729	1.908014137	1.951284061	2.018546908	2.120970603	2.221312286	2.326642926	2.484790077	2.697482124
0	0.416465712	0.839808608	1.257615298	1.594063829	1.746180569	1.844576945	1.908141808	1.95139359	2.018642797	2.121076208	2.221435366	2.326743421	2.484922416	2.697668774];

x=[0	1	2	3	4	5	6	7	8	10	14	20	30	50	80];
%plot(x(1:13),a(1:11:126,1:13))
hold on;
plot(x(1:10),a(84,1:10))