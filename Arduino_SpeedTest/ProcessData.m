format long

filename = 'SerialData.txt';
Data = importdata(filename);
Sample = split( Data,"41424344" );
Sample = Sample(2:end-1);
M = zeros(length(Sample),4);
M1 = zeros(length(Sample),4);

M = string(M);
for i=1:length(Sample)
    for j = 1:4
        if (length(Sample{i,1}) ~=16)
            Sample{i,1}='0000000000000000';
        end
        M(i,j) = Sample{i,1}((4*j-3):(4*j));      
        f = (hex2dec(M(i,j)));
        if (bitand(f,32768) == 32768)
            M1(i,j)= f - 65536;
        else
            M1(i,j)= f ;
        end
    end
end
 
zeroelements = all(M1 == 0,2);
zeroelements = find (zeroelements);
M1(zeroelements,:) = [];
M(zeroelements,:) = [];
M1(:,4) = hex2dec(M(:,4));
 
 time = zeros(length(M1),1);
 time(1) =0;
 for i= 2 : length(M1)
     if M1(i,4) < M1(i-1,4)
        time(i) = time(i-1) + M1(i,4) + (65536 - M1(i-1,4));
     else
         time(i) = time(i-1) + (M1(i,4)- M1(i-1,4));
     end
 end
 
 M1(:,4)= time;
 
 accX = M1(:,1)*0.000061037;
 accY = M1(:,2)*0.000061037;
 accZ = M1(:,3)*0.000061037;

time=time*0.000001;
 figure
 plot(time,accX);
 hold on;
 plot(time,accY);
 hold on;
 plot(time,accZ);
 
 title('Acceleration');
xlabel('time [s]');
ylabel('Accelereation [g]');
ylim([-2 2]);
 legend('AccX','Acc_Y','Acc_Z');
