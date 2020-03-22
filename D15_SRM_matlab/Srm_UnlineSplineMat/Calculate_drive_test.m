function dy=fun(t, y)
dy = zeros(2,1);
dy(1)=2*y(1)+y(2);
dy(2)=-3*y(1)+6*y(2);

ode23(@fun, ..., ...)