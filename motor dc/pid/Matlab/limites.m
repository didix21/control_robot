function [x,y]=limites(x,y)

    
    if x==0 && y==0
        rad=0;
        ang=0;
    else
        rad=sqrt((x^2)+(y^2));
        ang= (atan(y/x));        
    end

if rad>255
    if x>0
        den=sqrt(1+(tan(ang))^2);
        num=255*tan(ang);
        y=num/den;
        x=sqrt((255^2)-(y^2));
    else
        den=sqrt(1+(tan(ang))^2);
        num=255*tan(ang);
        y=-num/den;
        x=-sqrt((255^2)-(y^2));
    end
else
    x=x;
    y=y;
end
    