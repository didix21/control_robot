function print (x,y)
p=plot ([y 0], [x 0]);
set (p,'linewidth',2);
set (p,'MarkerSize',5);
set (p,'Marker','o');
if x<0
    x=-x;
end
if y<0
    y=-y;
end
ylim([-255 255]);
xlim([-255 255]);
grid

hold on
circle(0,0,255);
hold off
end