filename = 'giuse.txt';
%delimiterIn = "ABCD";
A = importdata(filename);
newStr = split( A,"41424344" );
yhat = newStr(2:end-1);
M = zeros(length(yhat),4);
Menu = zeros(length(yhat),4);

M = string(M);
for i=1:length(yhat)
    for j=1:4
        if (length(yhat{i,1}) ~=16)
            yhat{i,1}='0000000000000000';
        end
        M(i,j)= yhat{i,1}((4*j-3):(4*j));      
        f = (hex2dec(M(i,j)));
        if (bitand(f,32768) == 32768)
            Menu(i,j)= f -65536;
        else
            Menu(i,j)= f ;
        end
    end
end
 Menu=Menu(Menu~=0);
 Menu(:,4)= hex2dec(M(:,4));
 for (i=2:length(Menu))
     if Menu(i)<Menu(i-1)
Menutime(i) = Menu(i)+ (65536 -Menu(i-1));
     else Menutime(i) = Menutime(i-1) + (Menu(i)-Menu(i-1));
     Menu(i)= 65536-Menu(i)
 
