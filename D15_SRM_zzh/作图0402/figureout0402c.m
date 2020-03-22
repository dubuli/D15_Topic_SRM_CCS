
tt= jizhunU (:,1);
yy= jizhunU (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

hold on;

tt= jiaodu6051405U (:,1);
yy= jiaodu6051405U (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

hold on;

tt= jiaodu715U (:,1);
yy= jiaodu715U (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

set(gca,'Fontasize',12)


