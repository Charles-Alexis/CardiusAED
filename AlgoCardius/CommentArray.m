function [ComArray] = CommentArray(Ann,Com)

    ComArray = zeros(1,525000);
    ResArray = zeros(1,2100);
    
    condition1 = string('(VT');
    condition2 = string('(VFIB');
    condition3 = string('(VF');
    condition4 = string('(SVTA');
    
    Ann=floor(Ann/250);
    
    ResultShockable = 'S'; 
    ResultNonShockable = 'N'; 

    for i = 1:length(ResArray)
        if(i==1)
            p = Ann(i+1);
            val = string(Com{i}())
            if(val == condition1 || val == condition2 || val == condition3)
                val = char(ResultShockable)
            else
                val = char(ResultNonShockable)
            end
            for k = 1:p
                ComArray(k) = val;
            end
        elseif(i==length(Ann))
            p = Ann(i);
            val = char(Com{i}());
            if(val == condition1 || val == condition2 || val == condition3)
                val = char(ResultShockable)
            else
                val = char(ResultNonShockable)
            end
            for k = p:length(ComArray)
                ComArray(k) = val;
            end
        else
            p1 = Ann(i)+1;
            p2 = Ann(i+1);
            val =  char(Com{i}());
            if(val == condition1 || val == condition2 || val == condition3)
                val = char(ResultShockable)
            else
                val = char(ResultNonShockable)
            end
            for k = p1:p2
                ComArray(k) = val;
            end
        end
    end

    
end

