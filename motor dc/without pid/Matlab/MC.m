function MC (x,y,s)

if x>=0 && y~=0
    y=-y;
else
    y=y;
end
R=y+x;
L=y-x;
    
if R>255
    R=255;
else if R<-255
        R=-255;
    end
end

if L>255
    L=255;
else if L<-255
        L=-255;
    end
end

R=R
L=L
    str = int2str(R);
    send = ['r'  str 'z'];
    fwrite(s,send,'char','sync');
    pause (0.1);
    
    str = int2str(L);
    send = ['l'  str 'z'];
    fwrite(s,send,'char','sync');
    
end