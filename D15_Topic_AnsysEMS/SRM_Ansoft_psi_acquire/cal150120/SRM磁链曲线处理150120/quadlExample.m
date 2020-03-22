clc;clear;
%已知的数据
x=0:0.08:0.08*19;
y=[0	4.479775043	8.95976642	13.43874767	17.91561783	22.38976708	26.86108398	31.34276701	35.81661433	40.2995132	44.80984723	49.30227284	53.79953773	58.84685699	65.08839864	72.36482075	80.15442481	87.93376007	95.17937575	101.3678211];
plot(x,y,'ro');
%插值后得到的函数
f=@(t)interp1(x,y,t,'spline');
hold on;ezplot(f,[0,1.7]);
%变上限函数，下限为2
g=quad(f,0,1.4);