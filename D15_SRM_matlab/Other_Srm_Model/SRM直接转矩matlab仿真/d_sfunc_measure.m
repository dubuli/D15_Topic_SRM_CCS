function [sys,x0,str,ts] = d_sfunc_measure(t,x,u,flag,r)
%intput:u(1)-u(6)--Ua,ub,uc,ia,ib,ic
%state: x1:F change state,x2:Te change state,x3:s,x4:section
%       x5:Fa,x6:Fb,x7:sum det_speed,x8:pid output as Te*
%output:y1-y3----fa,fb,fc
switch flag,
    case 0,
    [sys,x0,str,ts] = mdlInitializeSizes;
   case 2,                                                
    sys = mdlUpdate(t,x,u,r); 
   case 3,                                                
    sys = mdlOutputs(t,x,u);
  case {1,4,9 }                                               
    sys = []; % do nothing
  otherwise
    error(['unhandled flag = ',num2str(flag)]);
end
function sys = mdlUpdate(t,x,u,r)
% *******************************************
% slove Fa,b,c
x(1)=x(1)+u(1)-u(4)*r;%fa
x(2)=x(2)+u(2)-u(5)*r;%fb
x(3)=x(3)+u(3)-u(6)*r;%fc

sys(1)=x(1); 
sys(2)=x(2); 
sys(3)=x(3); 


function sys = mdlOutputs(t,x,u)
sys(1)=x(1);
sys(2)=x(2);
sys(3)=x(3);


function [sys,x0,str,ts] = mdlInitializeSizes()
sizes = simsizes;
sizes.NumContStates  = 0;
sizes.NumDiscStates  =3;
sizes.NumOutputs     = 3;
sizes.NumInputs      = 6;
sizes.DirFeedthrough = 0;
sizes.NumSampleTimes =1;
sys = simsizes(sizes);
x0  =[0 0 0];
str = [];
ts  = [-1 0]; 

