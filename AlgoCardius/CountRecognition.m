function [C1,C2,C3,TreshholdLow1,TreshholdHigh1,TreshholdLow2,TreshholdHigh2,TreshholdLow3,TreshholdHigh3] = CountRecognition(Data)

TreshholdLow1 = zeros(1,2500);
TreshholdHigh1 = zeros(1,2500);
TreshholdLow2 = zeros(1,2500);
TreshholdHigh2 = zeros(1,2500);
TreshholdLow3 = zeros(1,2500);
TreshholdHigh3 = zeros(1,2500);

FilteredData = Data;

C1 = 0;
C2 = 0;
C3 = 0;

for SecEpoch = 1:10
        InSample = FilteredData((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1))));
  
        % Count1 Range in the Epcoh section
        Count1Low = 0.5 * max(abs(InSample));
        Count1High = max(abs(InSample));
        
        % Count2 Range in the Epcoh section
        Count2Low = mean(abs(InSample));
        Count2High = max(abs(InSample));
        
        % Count3 Range in the Epcoh section
        MD = sum(abs(abs(InSample)-mean(abs(InSample))))/length(InSample);
        Count3Low = mean(abs(InSample))-MD;
        Count3High = mean(abs(InSample))+MD;
        
        TreshholdLow1((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1)))) = Count1Low;
        TreshholdHigh1((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1)))) = Count1High;
        TreshholdLow2((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1)))) = Count2Low;
        TreshholdHigh2((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1)))) = Count2High;
        TreshholdLow3((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1)))) = Count3Low;
        TreshholdHigh3((1+(250*(SecEpoch-1))):(250+(250*(SecEpoch-1)))) = Count3High;
        
        for InSampleCount = 1:250
            if(InSampleCount == 250 && SecEpoch == 10)
                %break
            end
            if(InSample(InSampleCount) >= Count1Low && InSample(InSampleCount) <= Count1High)
                C1 = C1+1;
            end
            if(InSample(InSampleCount) >= Count2Low && InSample(InSampleCount) <= Count2High)
                C2 = C2+1;
            end
            if(InSample(InSampleCount) >= Count3Low && InSample(InSampleCount) <= Count3High)
                C3 = C3+1;
            end
        end
       
        
end

end

