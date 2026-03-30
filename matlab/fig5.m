load 'D:\STUDY\THESIS\Trajectories\Run12Aprofile600.txt';

x = Run12Aprofile600;
x1 = 0;
x2 = 0;
sizeX = size(x,1);
%avgX = zeros(sizeX,2);
hold on;
for i=1:size(x,1)
    x1 = x1+x(i,1);
    x2 = x2+x(i,2);
    %avgX(i,1) = x1/i;
    %avgX(i,2) = x2/i;
    %plot3(1:i,x(1:i,1),x(1:i,2));
    %pause(0.01);
end
plot3(1:i,x(:,1),x(:,2));
%figure;
%plot(x(:,1),x(:,2));
%plot3(1:i,avgX(:,1),avgX(:,2),'r');
hold off;
