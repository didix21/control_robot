function MC (x,y,s)

if x>=0 && y~=0
    y=-y;
else
    y=y;
end
R=int64((x+90)+(y));
L=int64((90-x)+(y));
    
if R>180
    R=180;
else if R<0
        R=0;
    else
        R=R;
    end
end

if L>180
    L=180;
else if L<0
        L=0;
    else
        L=L;
    end
end

%---Show r and l values in Matlab
% r=R-90
% l=-(L-90)


%--- Polar direction %DOn't work
% if x==0 && y==0
%     rad=0;
%     ang=0;
% else
%     rad=sqrt((x^2)+(y^2));
%     ang=radtodeg (atan(y/x));
% end
%     
% if x>=0
%     if y==0
%         R=rad;
%         L=rad;
%     else if y>0
%             R=rad*(1-ang/90);
%             L=-rad;
%         else if y<0
%                 R=rad*(1-(-ang/90));
%                 L=-rad;
%             end
%         end
%     end
% else
%     if y==0
%         R=-rad;
%         L=-rad;
%     else if y>0
%             R=-rad*ang/90;
%             L=-rad*(1+ang/90);
%         else if y<0
%                 R=-rad*(1-(ang/90));
%                 L=-rad*ang/90;
%             end
%         end
%     end
% end
% 
% r=R
% l=L
% R=int64 (R+90);
% L=180-int64 (L+90);
    

    str = int2str(R);
    send = ['r'  str 'z'];
    fwrite(s,send,'char','sync');
    pause (0.1);
    
    str = int2str(L);
    send = ['l'  str 'z'];
    fwrite(s,send,'char','sync');
    
end