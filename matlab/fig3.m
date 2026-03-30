load 'D:\PSprings\Analysis 12\MutationsMagnitude.txt';
load 'D:\PSprings\Analysis 12\NumMutations.txt';
load 'D:\PSprings\Analysis 12\ProfileEvaluation.txt';

data = ProfileEvaluation;
x = MutationsMagnitude;
y = NumMutations;
z = x(:,1)./y(:,1);
hold on;
plot(1:size(z),z);
plot(1:size(y,1),y(:,1),'r');
%figure;
xaxis = 1:size(data);
xaxis = xaxis*10;
plot(xaxis,data(:,7),'g');
hold off;
