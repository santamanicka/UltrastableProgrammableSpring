load 'D:\PSprings\Analysis 12\NumMutations.txt';

x = NumMutations;
hold on;
plot(1:size(x,1),x(:,1),'r');
plot(1:size(x,1),x(:,2),'b');
hold off;