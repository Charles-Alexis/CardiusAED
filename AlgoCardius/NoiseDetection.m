function [NoiseFlag] = NoiseDetection(Data2Test)
    NoiseFlag = 0;
    if(max(Data2Test)<0.00015)
       NoiseFlag = 1; 
    end
end

