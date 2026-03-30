load 'D:\PSprings\Analysis 12A\ProfileEvaluation.txt';

data = ProfileEvaluation;
datasize = size(data,1);
totalCnt = [];
dev = [];
tvzdist = [];

zaxis = zeros(5);
figure;
hold on;
for i=1:3:datasize
%     plot3(1:datasize,data(:,8),data(:,9),'b');
%     plot3(1:datasize,data(:,11),data(:,12),'g');
%     plot3(1:datasize,data(:,14),data(:,15),'r');
%     plot3(1:datasize,data(:,17),data(:,18),'m');
%     plot3(1:datasize,data(:,21),data(:,22),'c');
    %angles=[data(i,8) data(i,11) data(i,14) data(i,17) data(i,8)];
    %angleVels=[data(i,9) data(i,12) data(i,15) data(i,18) data(i,9)];
    %i=13;
    angles=[data(i,9) data(i,12) data(i,15) data(i,18) data(i,9)];
    angleVels=[data(i,10) data(i,13) data(i,16) data(i,19) data(i,10)];
    zaxis=zaxis+5;
    %plot3(zaxis,angles,angleVels);
    plot(angles,angleVels);
end
%plot3(zaxis,angles,angleVels,'LineWidth',10,'g');
i=13;
angles=[data(i,9) data(i,12) data(i,15) data(i,18) data(i,9)];
angleVels=[data(i,10) data(i,13) data(i,16) data(i,19) data(i,10)];
plot(angles,angleVels,'g--','LineWidth',5);
hold off;

% hold on;
% plot3(1:datasize,data(:,8),data(:,9),'b');
% plot3(1:datasize,data(:,11),data(:,12),'g');
% plot3(1:datasize,data(:,14),data(:,15),'r');
% plot3(1:datasize,data(:,17),data(:,18),'m');
% plot3(1:datasize,data(:,21),data(:,22),'c');
% hold off;

% hold on;
% plot(1:datasize,data(:,8),'b');
% plot(1:datasize,data(:,11),'g');
% plot(1:datasize,data(:,14),'r');
% plot(1:datasize,data(:,17),'m');
% plot(1:datasize,data(:,21),'c');
% hold off;
