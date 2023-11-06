function [res] = ComputPerc(Data)
    res = zeros(1,2100);
    % Filtering ATMArray
%     data = Data;
%     data1 = lowpass(data',30,250);
%     data2 = highpass(data1,1,250);
%     ATMArray = bandstop(data2, [59 61], 250);
%     Data = ATMArray';
    
    for k = 1:2090
        Data2Filter = Data(1 , ((k-1)*250)+1:2500+((k-1)*250));
        % BandPass Filter
        FilteredResult = BPFFilter(Data2Filter);
        % Absolute Value of Epoch
        AbsFiltredData = abs(FilteredResult);
        [C1,C2,C3,TreshholdLow1,TreshholdHigh1,TreshholdLow2,TreshholdHigh2,TreshholdLow3,TreshholdHigh3] = CountRecognition(AbsFiltredData);
        % Calcuating BPM Value
        bpm = CountBPM(FilteredResult);
        % Check if the counts makes it shockable or not
        flag = CheckIfShockable(C1,C2,C3);
        if((flag == 0 && bpm<180) || flag == 1 || flag == 2)
            res(k) = 'N';
        end
        if(flag == 3 || flag == 4)
            res(k) = 'S';
        end
        if((flag == 0 && bpm>180))
            res(k) = 'S';
        end
        res(2091:2100) = res(2090);
        
        % Reforge Res
        for i = 6:2094
            if(res(i) == 'S')
                mean = (res(i-5) + res(i-4) + res(i-3) + res(i-2) + res(i-1) + res(i) + res(i+1) + res(i+2) + res(i+3) + res(i+4))/10;
                if(mean <= 79)
                    for k = 1:10
                        res(i-6+k) = 'N';
                    end
                end
            end
            if(res(i) == 'N')
                mean = (res(i-5) + res(i-4) + res(i-3) + res(i-2) + res(i-1) + res(i) + res(i+1) + res(i+2) + res(i+3) + res(i+4))/10;
                if(mean >= 82)
                    for k = 1:10
                        res(i-6+k) = 'S';
                    end
                end
            end
        end

    end
end

