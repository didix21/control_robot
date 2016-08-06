function [val] = keyboard_in ()%s)
    
close all;    
kbhit=1;
while kbhit ~= '0'
    kbhit=waitforbuttonpress; %#ok<NASGU>
    kbhit=get(gcf,'currentcharacter');
    switch kbhit
        case 30         %Forward
            str = int2str(180);          % convert number to string to send
            command='a';
            val='Endavant'
        case 31         %Backward
            str = int2str(0);
            command='f';
            val='Endarrera'
        case 29         %right
            str = int2str(180);
            command='r';
            val='dreta'
        case 28         %left
            str = int2str(180);
            command='l';
            val='esquerra'
        case '0'
            str=int2str(90);
            command='S';
        otherwise
            val='Error'
    end
    send = [command  str 'z'];
    fwrite(s,send,'char','sync');
end


end