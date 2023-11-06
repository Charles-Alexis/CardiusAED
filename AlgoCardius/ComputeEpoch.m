function [Result] = ComputeEpoch(Data2Test)
    % Analogue Filtering

    % Noise and Asystoly Detection
    NoiseFlag = NoiseDetection(Data2Test);
    if(NoiseFlag == 1)
        display('Noise or Asystoly') %Can't use DEA
        Result = -1;
        return
    end

    % BandPass Filter
    FilteredData = BPFFilter(Data2Test);

    % Absolute Value of Epoch
    AbsFiltredData = abs(FilteredData);

    % Count Recognition
    [C1,C2,C3] = CountRecognition(AbsFiltredData);

    % Classification
    Result = CheckIfShockable(C1,C2,C3);

    % Display
    if(Result == 0)
        display('Cannot classify Epoch')
    end

    if(Result == 1 || Result == 2)
        display('Non-Shockable Epoch')
    end

    if(Result == 3 || Result == 4)
        display('Shockable Epoch')
    end
end

