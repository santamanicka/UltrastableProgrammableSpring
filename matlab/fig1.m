load 'D:\PSprings\Analysis 12\ProfileEvaluation.txt';

data = ProfileEvaluation;
datasize = size(data,1);
totalCnt = [];
dev = [];
tvzdist = [];

for i=1:datasize
    zone0 = data(i,1);
    zone1 = data(i,2);
    zone2 = data(i,3);
    zone3 = data(i,4);
    total = zone0+zone1+zone2+zone3;
    avg = total/4;
    diff = (zone0-avg)^2+(zone1-avg)^2+(zone2-avg)^2+(zone3-avg)^2;
    diff = diff/4;
    stddev = sqrt(diff);
    totalCnt = [totalCnt total]; %#ok<AGROW>
    dev = [dev stddev]; %#ok<AGROW>
    %tvzdist = [tvzdist data(i, 8)]; %#ok<AGROW>
end

hold on;
plot(1:datasize,totalCnt,'b');
plot(1:datasize,dev,'r');
%plot(1:datasize,totalCnt-2*dev,'g');
%plot(1:datasize, tvzdist,'g');
hold off;

% cumVal=0;
% avgDev=[];
% for i=1:size(dev,2)
%     cumVal = cumVal+dev(i);
%     avgDev = [avgDev (cumVal/i)]; %#ok<AGROW>
% end
% figure;
% plot(1:size(dev,2),avgDev);