function [ResArray] = ComAr(Ann,Com)
    condition1 = string('(VT');
    condition2 = string('(VFIB');
    condition3 = string('(VF');
    condition4 = string('(SVTA');
    ResultShockable = 'S'; 
    ResultNonShockable = 'N';
    
    ResArray = zeros(1,2100);
    Ann=floor(Ann/250)+1;
    
    % Placing Milestones
    for i = 1:length(Ann)
        val = string(Com{i}());
        if(val == condition1 || val == condition2 || val == condition3)
            val = char(ResultShockable);
        else
            val = char(ResultNonShockable);
        end        
        if(i==1)
            ResArray(1:Ann(2)-1) = val;
        elseif(i==length(Ann))
            ResArray(Ann(i):length(ResArray)) = val;
        else
            ResArray(Ann(i):Ann(i+1)-1) = val;
    end
    
    
end

