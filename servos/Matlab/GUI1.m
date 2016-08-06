function varargout = GUI1(varargin)
% GUI1 MATLAB code for GUI1.fig
%      GUI1, by itself, creates a new GUI1 or raises the existing
%      singleton*.
%
%      H = GUI1 returns the handle to a new GUI1 or the handle to
%      the existing singleton*.
%
%      GUI1('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI1.M with the given input arguments.
%
%      GUI1('Property','Value',...) creates a new GUI1 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI1_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI1_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI1

% Last Modified by GUIDE v2.5 05-Apr-2016 11:45:13

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI1_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI1_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI1 is made visible.
function GUI1_OpeningFcn(hObject, eventdata, handles, varargin)



%Control inizialitation
set(handles.control_panel,'visible','off');
set(handles.select_panel,'visible','off');

%Graphic initialization
set(handles.Graph,'visible','off');
set(handles.axis_info,'visible','off');

set(handles.connect_button,'visible','on');
set(handles.connect_button,'string','Disconnected');
set(handles.connect_button,'backgroundcolor','r');





% Choose default command line output for GUI1
handles.output = hObject;
handles.serial_port=hObject;
handles.serial_port=Ini_Port;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI1 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = GUI1_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes when user attempts to close figure1.
function figure1_CloseRequestFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%-------------------------------------------------------------fclose (handles.serial_port);
%-------------------------------------------------------------delete(handles.serial_port);
% Hint: delete(hObject) closes the figure
delete(hObject);


% --- Executes during object creation, after setting all properties.
function x_info_CreateFcn(hObject, eventdata, handles)
% hObject    handle to x_info (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                      CONNECT                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --- Executes on button press in connect_button.
function connect_button_Callback(hObject, eventdata, handles)

    %Initiale conditions
    str= (get(hObject,'string'));
    set(handles.x_info,'string',0);
    set(handles.y_info,'string',0);
    print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
    
   
if str(1) == 'D'
     %To connect
    %----------------------------------------fopen (handles.serial_port);
     
    %hide control panels, and show select panel
    set(handles.axis_info,'visible','off');
    set(handles.pad,'visible','off');
    set(handles.Graph,'visible','off');
    set(handles.select_panel,'visible','on');
    
    %Chande button connecction to green
    set(handles.connect_button,'string','Connected');
    set(handles.connect_button,'backgroundcolor','g');
    
    %Anyone control selected, all buttons in red
    set(handles.slider_select,'backgroundcolor','r');
    set(handles.pad_select,'backgroundcolor','r');
    set(handles.kb_select,'backgroundcolor','r');
    set(handles.mouse_select,'backgroundcolor','r');
    
else
    
    %To disconnect
    set(handles.x_info,'string',0);
    set(handles.y_info,'string',0);
    MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);
    %-----------------------------fclose (handles.serial_port);
    
    %hide all controls and select panels
    set(handles.axis_info,'visible','off');
    set(handles.control_panel,'visible','off');
    set(handles.Graph,'visible','off');
    set(handles.select_panel,'visible','off');
    

    %Change button connection to red
    set(handles.connect_button,'string','Disconnected');
    set(handles.connect_button,'backgroundcolor','r');
    
end
    


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%           SELECTION BUTTONS                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --- Executes on button press in slider_select.
function slider_select_Callback(hObject, eventdata, handles)

%initiale conditions
set(handles.x_info,'string',0);
set(handles.y_info,'string',0);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
set(handles.x_info,'backgroundcolor','w');
set(handles.y_info,'backgroundcolor','w');

% Color buttons
set (hObject,'backgroundcolor','g');
set (handles.pad_select,'backgroundcolor','r');
set (handles.kb_select,'backgroundcolor','r');
set (handles.mouse_select,'backgroundcolor','r');

% show and hide commands
    %Axis panel
    set(handles.axis_info,'visible','on');
    set(handles.send_label,'visible','off');
    set(handles.Mouse_p_label,'visible','off');
    set(handles.mouse_x,'visible','off');
    set(handles.mouse_y,'visible','off');
    
    %controls and graph
    set(handles.pad,'visible','off');
    set(handles.slider,'visible','on');
    set(handles.control_panel,'visible','on');
    set(handles.Graph,'visible','on');

MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in pad_select.
function pad_select_Callback(hObject, eventdata, handles)

%initiale conditions
set(handles.x_info,'string',0);
set(handles.y_info,'string',0);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
set(handles.x_info,'backgroundcolor','w');
set(handles.y_info,'backgroundcolor','w');

%show pad buttons 
set (handles.up_button,'visible','on');
set (handles.down_button,'visible','on');
set (handles.left_button,'visible','on');
set (handles.right_button,'visible','on');
set (handles.stop_button1,'visible','on');
set(handles.pad,'backgroundcolor','w');

%Buttons to color of selection
set (hObject,'backgroundcolor','g');
set (handles.slider_select,'backgroundcolor','r');
set (handles.kb_select,'backgroundcolor','r');
set (handles.mouse_select,'backgroundcolor','r');

%Show control panel selected
set(handles.control_panel,'visible','on');
set(handles.pad,'visible','on');
set(handles.slider,'visible','off');
set (handles.pad,'Title','PAD control');

%Show axis and plot
set(handles.axis_info,'visible','on');
set(handles.Graph,'visible','on');
set(handles.send_label,'visible','off');
set(handles.Mouse_p_label,'visible','off');
set(handles.mouse_x,'visible','off');
set(handles.mouse_y,'visible','off');

MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in mouse_select.
function mouse_select_Callback(hObject, eventdata, handles)
% hObject    handle to mouse_select (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%initiale conditions
set(handles.x_info,'string',0);
set(handles.y_info,'string',0);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))

set(handles.x_info,'backgroundcolor',[0.9 0.9 0.9]);
set(handles.y_info,'backgroundcolor',[0.9 0.9 0.9]);

%hide pad buttons 
set (handles.up_button,'visible','off');
set (handles.down_button,'visible','off');
set (handles.left_button,'visible','off');
set (handles.right_button,'visible','off');
set (handles.stop_button1,'visible','off');

%Buttons to color of selection
set (hObject,'backgroundcolor','g');
set (handles.slider_select,'backgroundcolor','r');
set (handles.kb_select,'backgroundcolor','r');
set (handles.pad_select,'backgroundcolor','r');

%Show control panel selected
set(handles.control_panel,'visible','on');
set(handles.pad,'visible','off');
set(handles.slider,'visible','off');
set (handles.pad,'Title','PAD control');

%Show axis and plot
set(handles.axis_info,'visible','on');
set(handles.Graph,'visible','on');
set(handles.send_label,'visible','on');
set(handles.Mouse_p_label,'visible','on');
set(handles.mouse_x,'visible','on');
set(handles.mouse_y,'visible','on');

MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in kb_select.
function kb_select_Callback(hObject, eventdata, handles)

%initiale conditions
set(handles.x_info,'string',0);
set(handles.y_info,'string',0);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
set(handles.x_info,'backgroundcolor','w');
set(handles.y_info,'backgroundcolor','w');

%Buttons to color of selection
set (hObject,'backgroundcolor','g');
set (handles.slider_select,'backgroundcolor','r');
set (handles.pad_select,'backgroundcolor','r');
set (handles.mouse_select,'backgroundcolor','r');

%Control panel
set (handles.control_panel,'visible','on');
set (handles.slider,'visible','off');
set (handles.pad,'Title','Keyboard control');
set (handles.pad,'visible','on');

%Pad Buttons and backgroundcolor
set (handles.up_button,'visible','on');
set (handles.down_button,'visible','on');
set (handles.left_button,'visible','on');
set (handles.right_button,'visible','on');
set (handles.stop_button1,'visible','on');
set(handles.pad,'backgroundcolor','y');


%Show axis and plot
set(handles.axis_info,'visible','on');
set(handles.Graph,'visible','on');
set(handles.send_label,'visible','off');
set(handles.Mouse_p_label,'visible','off');
set(handles.mouse_x,'visible','off');
set(handles.mouse_y,'visible','off');

MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                      PAD                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --- Executes on button press in up_button.
function up_button_Callback(hObject, eventdata, handles)

%Get value from edit text and convert in double
x=str2double(get(handles.x_info,'string'));
y=str2double(get(handles.y_info,'string'));

%limit value until 255 (Maximum PWM)
x=x+5;
if x>90
    x=90;
end
[x,y]=limites(x,y);
set(handles.x_info,'string',x);
set(handles.y_info,'string',y);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in left_button.
function left_button_Callback(hObject, eventdata, handles)
%Get value from edit text and convert in double
x=str2double(get(handles.x_info,'string'));
y=str2double(get(handles.y_info,'string'));

%limit value until 255 (Maximum PWM)
y=y-5;
if y<-90
    y=-90;
end
[x,y]=limites(x,y);
set(handles.x_info,'string',x);
set(handles.y_info,'string',y);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in right_button.
function right_button_Callback(hObject, eventdata, handles)
%Get value from edit text and convert in double
x=str2double(get(handles.x_info,'string'));
y=str2double(get(handles.y_info,'string'));

%limit value until 255 (Maximum PWM)
y=y+5;
if y>90
    y=90;
end
[x,y]=limites(x,y);
set(handles.x_info,'string',x);
set(handles.y_info,'string',y);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in down_button.
function down_button_Callback(hObject, eventdata, handles)
%Get value from edit text and convert in double
x=str2double(get(handles.x_info,'string'));
y=str2double(get(handles.y_info,'string'));
%limit value until 255 (Maximum PWM)
x=x-5;
if x<-90
    x=-90;
end
[x,y]=limites(x,y);
set(handles.x_info,'string',x);
set(handles.y_info,'string',y);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes on button press in stop_button1.
function stop_button1_Callback(hObject, eventdata, handles)
set(handles.x_info,'string',0);
set(handles.y_info,'string',0);
print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                      SLIDER                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --- Executes on slider movement.
function sliderX_Callback(hObject, eventdata, handles)

set(handles.x_info,'string',get(hObject,'Value'));

%Get value from edit text and convert in double
x=str2double(get(handles.x_info,'string'));
y=str2double(get(handles.y_info,'string'));

[x,y]=limites(x,y);
set(handles.x_info,'string',x);
set(handles.y_info,'string',y);

print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes during object creation, after setting all properties.
function sliderX_CreateFcn(hObject, ~, handles)
% hObject    handle to sliderX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function sliderY_Callback(hObject, eventdata, handles)

set(handles.y_info,'string',get(hObject,'Value'));

%Get value from edit text and convert in double
x=str2double(get(handles.x_info,'string'));
y=str2double(get(handles.y_info,'string'));

[x,y]=limites(x,y);
set(handles.x_info,'string',x);
set(handles.y_info,'string',y);


print (str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')))
MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);

% --- Executes during object creation, after setting all properties.
function sliderY_CreateFcn(hObject, eventdata, handles)
% hObject    handle to sliderX (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in stop_button2.
function stop_button2_Callback(hObject, eventdata, handles)
    stop_button1_Callback(hObject, eventdata, handles)
    set (handles.sliderX,'Value',0);
    set (handles.sliderY,'Value',0);


    

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                  KEYBOARD                           %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% --- Executes on key press with focus on figure1 or any of its controls.
function figure1_WindowKeyPressFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  structure with the following fields (see FIGURE)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)
h=get(handles.kb_select,'backgroundcolor');
if h==[0 1 0]
set (handles.control_panel,'visible','on');
switch eventdata.Key
    case 'w'         %Forward
        command='a';
        val='Endavant';
        set (handles.up_button,'visible','on');
        set (handles.down_button,'visible','off');
        set (handles.left_button,'visible','off');
        set (handles.right_button,'visible','off');
        set (handles.stop_button1,'visible','off');
        up_button_Callback(hObject, eventdata, handles)
        str = get(handles.x_info,'string');
    case 's'         %Backward
        str = int2str(0);
        command='f';
        val='Endarrera';
        set (handles.up_button,'visible','off');
        set (handles.down_button,'visible','on');
        set (handles.left_button,'visible','off');
        set (handles.right_button,'visible','off');
        set (handles.stop_button1,'visible','off');
        down_button_Callback(hObject, eventdata, handles)
    case 'd'         %right
        str = int2str(180);
        command='r';
        val='dreta';
        set (handles.up_button,'visible','off');
        set (handles.down_button,'visible','off');
        set (handles.left_button,'visible','off');
        set (handles.right_button,'visible','on');
        set (handles.stop_button1,'visible','off');
        right_button_Callback(hObject, eventdata, handles)
    case 'a'         %left
        str = int2str(180);
        command='l';
        val='esquerra';
        set (handles.up_button,'visible','off');
        set (handles.down_button,'visible','off');
        set (handles.left_button,'visible','on');
        set (handles.right_button,'visible','off');
        set (handles.stop_button1,'visible','off');
        left_button_Callback(hObject, eventdata, handles)
    case ' '
        str=int2str(90);
        command='S';
        set (handles.up_button,'visible','off');
        set (handles.down_button,'visible','off');
        set (handles.left_button,'visible','off');
        set (handles.right_button,'visible','off');
        set (handles.stop_button1,'visible','on');
        stop_button1_Callback(hObject, eventdata, handles)
    otherwise
        val='Error';
        set (handles.up_button,'visible','off');
        set (handles.down_button,'visible','off');
        set (handles.left_button,'visible','off');
        set (handles.right_button,'visible','off');
        set (handles.stop_button1,'visible','off');
end

end

% --- Executes on key release with focus on figure1 or any of its controls.
function figure1_WindowKeyReleaseFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  structure with the following fields (see FIGURE)
%	Key: name of the key that was released, in lower case
%	Character: character interpretation of the key(s) that was released
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) released
% handles    structure with handles and user data (see GUIDATA)
        set (handles.up_button,'visible','off');
        set (handles.down_button,'visible','off');
        set (handles.left_button,'visible','off');
        set (handles.right_button,'visible','off');
        set (handles.stop_button1,'visible','off');


        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                    MOUSE                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% --- Executes on mouse motion over figure - except title and menu.
function figure1_WindowButtonMotionFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
%handles    structure with handles and user data (see GUIDATA)
if get (handles.mouse_select,'backgroundcolor')== [0 1 0 ]
    pos = get(hObject, 'currentpoint'); % get mouse location on figure
    x = pos(2); y = pos(1); % assign locations to x and y

    x=(x-17)*6;
    if x<0
        x=0;
    else if x>180
        x=180;
        end
    end
    x=x-90;
    
    y=(y-90)*2;
    if y<0
        y=0;
    else if y>180
        y=180;
        end
    end
    y=y-90;
    set(handles.mouse_x, 'string', x); % update text for x loc
    set(handles.mouse_y, 'string', y); % update text for y loc 
end

% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.
function figure1_WindowButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


if get (handles.mouse_select,'backgroundcolor')== [0 1 0 ]
    pos = get(hObject, 'currentpoint'); % get mouse location on figure
    x = pos(2); y = pos(1); % assign locations to x and y
    x=(x-17)*6;
    if x<0
        x=0;
        set(handles.x_info,'backgroundcolor','r');
    else if x>180
        x=180;
        set(handles.x_info,'backgroundcolor','r');
        else
          set(handles.x_info,'backgroundcolor','w');
        end
    end
    

    y=(y-90)*2;
    if y<0
        y=0;
        set(handles.y_info,'backgroundcolor','r');
    else if y>180
        y=180;
        set(handles.y_info,'backgroundcolor','r');
        else
            set(handles.y_info,'backgroundcolor','w');
        end
    end
    x=x-90;
    y=y-90;
    [x,y]=limites(x,y);

    set(handles.x_info, 'string', x); % update text for x loc 
    
    set(handles.y_info, 'string', y); % update text for y loc 
    print (x,y);
    MC(str2double(get(handles.x_info,'string')),str2double(get(handles.y_info,'string')),handles.serial_port);
end


% --- Executes on mouse press over figure background, over a disabled or
% --- inactive control, or over an axes background.
function figure1_WindowButtonUpFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if get (handles.mouse_select,'backgroundcolor')== [0 1 0 ]
    pos = get(hObject, 'currentpoint'); % get mouse location on figure
    x = pos(2); y = pos(1); % assign locations to x and y
    x=(x-17)*6;
    if x<0
        x=0;
    else if x>180
        x=180;
        end
    end
    x=x-90;
    
    y=(y-90)*2;
    if y<0
        y=0;
    else if y>180
        y=180;
        end
    end
    y=y-90;

    set(handles.x_info, 'string', x); % update text for x loc
    set(handles.y_info, 'string', y); % update text for y loc 
    set(handles.x_info,'backgroundcolor',[0.9 0.9 0.9]);
    set(handles.y_info,'backgroundcolor',[0.9 0.9 0.9]);
end


