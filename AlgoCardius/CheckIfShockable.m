
function [flag] = CheckIfShockable(Count1,Count2,Count3)
    flag=0;
    %Non shockable
    if(Count1<250 && Count2 > 950 && (Count1*Count2/Count3) < 210)
    
        flag = 1;
        return
    end
    
    if(Count1 >= 250 && Count1<400 && Count2 < 600 && (Count1*Count2/Count3) < 210)
        flag = 2;
        return
    end
    
    %shockable
    if(Count1 >= 250 && Count2 > 950)
        flag = 3;
        return
    end
    
    if(Count2 > 1100)
        flag = 4;
        return
    end
end

