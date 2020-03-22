
tt= jizhunU (:,1);
yy= jizhunU (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

% axis([0,0.3,0,350])
xlim([0,0.3])
    
hold on;

tt= wenyadianrong500U (:,1);
yy= wenyadianrong500U (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

hold on;

tt= wenyadianrong1500U (:,1);
yy= wenyadianrong1500U (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');



set(gca,'Fontasize',12)


