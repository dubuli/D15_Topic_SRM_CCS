
tt= jizhunU (:,1);
yy= jizhunU (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

% axis([0,0.3,0,350])
xlim([0,0.3])
    
hold on;

tt= zhuansu500U (:,1);
yy= zhuansu500U (:,2);
plot(tt,yy);
xlabel('t/s ');
ylabel('U/V ');

hold on;

% tt= jiaodu715U (:,1);
% yy= jiaodu715U (:,2);
% plot(tt,yy);
% xlabel('t/s ');
% ylabel('U/V ');



set(gca,'Fontasize',12)


