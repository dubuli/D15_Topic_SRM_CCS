     clc
     clear
     I=[0 50	100	150	200	250	300	400	500	600	700	800	1000	1250 1500
  ];
     Flux=[0 0.008259925	0.01651985	0.024782672	0.033048445	0.041312086	0.049570652	0.066000553	0.081206045	0.092744086	0.100974442	0.106641964	0.114899438	0.123309812 0.131077575

];
 FluxFlux=[0 0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.11 0.12 0.13 0.14];
     for i=1:15
         p(i)=FluxFlux(i);
         q(i)=interp1(Flux,I,p(i),'spline');
     end
p'
q'
xi=0:0.001:0.14;
pp=csape(p,q,'second',[0, 0]);
yi1=ppval(pp,xi);
plot(Flux,I,'*',xi,yi1,'r')
pp2=csape(Flux,I,'second',[0, 0]);
yi2=ppval(pp2,xi);
figure;
plot(xi,yi2,Flux,I,'*')

figure;
plot(Flux,I,'*',p,q,'-')


