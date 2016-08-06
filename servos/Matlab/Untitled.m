
while(1)
h_fig = figure;
set(h_fig,'KeyPressFcn',@(h_obj,evt) disp(evt.Key));
end