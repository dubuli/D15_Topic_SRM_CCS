function [sys,x0,str,ts] = d_sfunc_dtc(t,x,u,flag,Fset,Speed,Kp,Ki,Temax)
%intput:u(1)-u(5)--fa,fb,fc,Te,n
%state: x1:F change state,x2:Te change state,x3:s,x4:section
%       x5:Fa,x6:Fb,x7:sum det_speed,x8:pid output as Te*
%output:y1:s,y2:section,y3:Fa,y4:Fb
switch flag,
    case 0,
    [sys,x0,str,ts] = mdlInitializeSizes;
   case 2,                                                
    sys = mdlUpdate(t,x,u,Fset,Speed,Kp,Ki,Temax); 
   case 3,                                                
    sys = mdlOutputs(t,x,u);
  case {1,4,9 }                                               
    sys = []; % do nothing
  otherwise
    error(['unhandled flag = ',num2str(flag)]);
end
function sys = mdlUpdate(t,x,u,Fset,Speed,Kp,Ki,Temax)
% *******************************************
% slove Fs and delta
Fa=u(1)-0.5*u(2)-0.5*u(3);% 3/2
Fb=0.86605*(u(2)-u(3));% 3/2 :0.86605=sqrt(3)/2
Fs=sqrt(Fa*Fa+Fb*Fb);
if (abs(Fa)<1e-5)
    Fa=1e-5;
end
Fba=Fb/Fa;
delta=atan(Fba);% pi/2 ~ -pi/2
if (Fa<0)
    delta=delta+pi; % -pi/2 ~ 3pi/2
end
%***************************************************
det_speed=Speed-u(5);
sum_det=x(7)+det_speed;
% if (sum_det*Ki>Temax*3)%limited sum_det
%     sum_det=Temax*3/Ki;
% end
% if (sum_det*Ki<-Temax*3)%limited sum_det
%     sum_det=-Temax*3/Ki;
% end
x(8)=det_speed*Kp+sum_det*Ki;%pid output as Te*
if x(8)>Temax        %limited Temax
    x(8)=Temax;
end
if x(8)<-Temax
    x(8)=-Temax;
end
% **************************************************
% s=1:00, T-,  phir-  s=2:01, T-,  phir+ 
% s=3:10, T+,  phir-  s=4:11, T+,  phir+

if (Fset-Fs)/Fset>0.005
    x(1)=1;
end
if (Fset-Fs)/Fset<-0.005
    x(1)=0;
end
if (x(8)-u(4))/x(8)>0.005
    x(2)=1;
end
if (x(8)-u(4))/x(8)<-0.005
    x(2)=0;
end
x(3)=x(2)*2+x(1)+1;%s=x(2)*2+x(1)+1;
% ******************************************
%  slove section based on delta
% 1:     0-60   2:   60-120  3:  120-180 
% 4:  180-240   5:  240-300  6:  300-360

if (delta<0)
  delta=delta+2*pi;  % -pi/2 ~ 3pi/2 --->0~ 2pi
end
x(4)=ceil(delta*360/(2*pi*60));%section=ceil(delta/60)
% ******************************************************
x(5)=Fa;
x(6)=Fb;
sys(1)=x(1); %if abs(Fset-Fs)<=0.005    x(1) no change
sys(2)=x(2); %if abs(Tset-u(4))<=0.005  x(2) no change
sys(3)=x(3); 
sys(4)=x(4); 
sys(5)=x(5); 
sys(6)=x(6); 
sys(7)=sum_det;
sys(8)=x(8);

function sys = mdlOutputs(t,x,u)
sys(1)=x(3);
sys(2)=x(4);
sys(3)=x(5);
sys(4)=x(6);

function [sys,x0,str,ts] = mdlInitializeSizes()
sizes = simsizes;
sizes.NumContStates  = 0;
sizes.NumDiscStates  =8;
sizes.NumOutputs     = 4;
sizes.NumInputs      = 5;
sizes.DirFeedthrough = 0;
sizes.NumSampleTimes =1;
sys = simsizes(sizes);
x0  =[1 1 1 1 0.001 0.001 0 0];
str = [];
ts  = [-1 0]; 

