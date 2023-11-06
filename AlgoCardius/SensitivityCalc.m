function [Sensitivity, Specificity] = SensitivityCalc(Input,Com)
TotalCount = 0;
Count = 0;
for i = 1:length(Input)
    if Com(i) == 83
        TotalCount = TotalCount + 1;
        if Com(i) == Input(i)
           Count = Count + 1; 
        end
    end
end
Sensitivity = Count/TotalCount*100;

TotalCount = 0;
Count = 0;
for i = 1:length(Input)
    if Com(i) == 78
        TotalCount = TotalCount + 1;
        if Com(i) == Input(i)
           Count = Count + 1; 
        end
    end
end
Specificity = Count/TotalCount*100;
end

