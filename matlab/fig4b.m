load 'D:\PSprings\Analysis 12\MutatedAngles.txt';
load 'D:\PSprings\Analysis 12\NotMutatedAngles.txt';

data = MutatedAngles;
notdata = NotMutatedAngles;
datasize = size(data,2);
notdatasize = size(notdata,2);

index=1;
notindex=1;
xaxis = 0;
readnext=1;
space = 0;

figure;
hold on;
for i=1:datasize
    if(readnext && notindex<=notdatasize)
        notangle = notdata(notindex);
        if(notangle == -999)
            readnext = 0;
            notindex = notindex+1;
        else
            if(mod(space,10)==0)
                plot(xaxis, notangle, 'r*');
            end
            notindex = notindex+1;
        end
    end
    angle = data(i);
    if(angle == -999)
        xaxis = xaxis+1;
        readnext = 1;
        space = space+1;
    else
        if(mod(space,10)==0)
            plot(xaxis, angle, 'b*');
        end
    end
end
hold off;

%plot3(1:size(minvals,2),minvals,maxvals);