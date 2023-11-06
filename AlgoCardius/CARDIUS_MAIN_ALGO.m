% All Mat files are from:
% https://archive.physionet.org/cgi-bin/atm/ATM
% 
% #todo: Inclure l'étude pour la license et les copyright


% INSTALLING WDFB TOOLBOX
% cd 'U:\S7\Algo CARDIUS\wfdb-app-toolbox-0-10-0'
% 
% [old_path]=which('rdsamp'); if(~isempty(old_path)) rmpath(old_path(1:end-8)); end
% wfdb_url='https://physionet.org/physiotools/matlab/wfdb-app-matlab/wfdb-app-toolbox-0-10-0.zip';
% [filestr,status] = urlwrite(wfdb_url,'wfdb-app-toolbox-0-10-0.zip');
% unzip('wfdb-app-toolbox-0-10-0.zip');
% cd mcode
% addpath(pwd)
% savepath
% 
% wfdbdemo

% Count definitions
% Count1 = 0.5 max(absFS) to max(absFS)
% Count2 = mean(absFs) to max(absFs)
% Count3 = mean(absFS) - MD to mean(absFS) + MD


clear all
%% 
clc
close all

%% Test Filter

[a,b]=butter(1,30/250,'low');

%% Load Data V2
ATM418 = PreFilter('418m');
ATM419 = PreFilter('419m');
ATM420 = PreFilter('420m');
ATM421 = PreFilter('421m');
ATM422 = PreFilter('422m');
ATM423 = PreFilter('423m');
ATM424 = PreFilter('424m');
ATM425 = PreFilter('425m');
ATM426 = PreFilter('426m');
ATM427 = PreFilter('427m');
ATM428 = PreFilter('428m');
ATM429 = PreFilter('429m');
ATM430 = PreFilter('430m');
ATM602 = PreFilter('602m');
ATM605 = PreFilter('605m');
ATM607 = PreFilter('607m');
ATM609 = PreFilter('609m');
ATM610 = PreFilter('610m');
ATM611 = PreFilter('611m');
ATM612 = PreFilter('612m');
ATM614 = PreFilter('614m');
ATM615 = PreFilter('615m');

[ann418,anntype,subtype,chan,num,comments418]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/418','atr');
[ann419,anntype,subtype,chan,num,comments419]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/419','atr');
[ann420,anntype,subtype,chan,num,comments420]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/420','atr');
[ann421,anntype,subtype,chan,num,comments421]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/421','atr');
[ann422,anntype,subtype,chan,num,comments422]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/422','atr');
[ann423,anntype,subtype,chan,num,comments423]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/423','atr');
[ann424,anntype,subtype,chan,num,comments424]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/424','atr');
[ann425,anntype,subtype,chan,num,comments425]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/425','atr');
[ann426,anntype,subtype,chan,num,comments426]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/426','atr');
[ann427,anntype,subtype,chan,num,comments427]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/427','atr');
[ann428,anntype,subtype,chan,num,comments428]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/428','atr');
[ann429,anntype,subtype,chan,num,comments429]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/429','atr');
[ann430,anntype,subtype,chan,num,comments430]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/430','atr');
[ann602,anntype,subtype,chan,num,comments602]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/602','atr');
[ann605,anntype,subtype,chan,num,comments605]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/605','atr');
[ann607,anntype,subtype,chan,num,comments607]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/607','atr');
[ann609,anntype,subtype,chan,num,comments609]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/609','atr');
[ann610,anntype,subtype,chan,num,comments610]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/610','atr');
[ann611,anntype,subtype,chan,num,comments611]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/611','atr');
[ann612,anntype,subtype,chan,num,comments612]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/612','atr');
[ann614,anntype,subtype,chan,num,comments614]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/614','atr');
[ann615,anntype,subtype,chan,num,comments615]=rdann('mit-bih-malignant-ventricular-ectopy-database-1.0.0/615','atr');

ComArray418 = ComAr(ann418,comments418);
ComArray419 = ComAr(ann419,comments419);
ComArray420 = ComAr(ann420,comments420);
ComArray421 = ComAr(ann421,comments421);
ComArray422 = ComAr(ann422,comments422);
ComArray423 = ComAr(ann423,comments423);
ComArray424 = ComAr(ann424,comments424);
ComArray425 = ComAr(ann425,comments425);
ComArray426 = ComAr(ann426,comments426);
ComArray427 = ComAr(ann427,comments427);
ComArray428 = ComAr(ann428,comments428);
ComArray429 = ComAr(ann429,comments429);
ComArray430 = ComAr(ann430,comments430);
ComArray602 = ComAr(ann602,comments602);
ComArray605 = ComAr(ann605,comments605);
ComArray607 = ComAr(ann607,comments607);
ComArray609 = ComAr(ann609,comments609);
ComArray610 = ComAr(ann610,comments610);
ComArray611 = ComAr(ann611,comments611);
ComArray612 = ComAr(ann612,comments612);
ComArray614 = ComAr(ann614,comments614);
ComArray615 = ComAr(ann615,comments615);


%% Sequence Settings
EpochTime = 10; %10Sec
SamplingFrequency = 250 ; %250Hz
EpochSampleLength = EpochTime*SamplingFrequency; %2500 Samples in a 10Sec epcohs
SamplingTime = 1/SamplingFrequency; %400uSec
TimeForEpoch = 0:SamplingTime:EpochTime-SamplingTime;


%% Count Computation for 10 sec
% Section of Data to analyse
pos =25;
TestData = ATM419(1,1+(2500*pos):EpochSampleLength+(2500*pos));
Data2Filter = TestData;

% BandPass Filter
FilteredResult = BPFFilter(Data2Filter);

% Absolute Value of Epoch
AbsFiltredData = abs(FilteredResult);
[C1,C2,C3,TreshholdLow1,TreshholdHigh1,TreshholdLow2,TreshholdHigh2,TreshholdLow3,TreshholdHigh3] = CountRecognition(AbsFiltredData);

% Calcuating BPM Value
bpm = CountBPM(FilteredResult);

% Ploting Data with Count Threshold
plot(AbsFiltredData,'m','LineWidth',1);hold on; 
plot(TreshholdLow1,'b--','LineWidth',2);hold on
plot(TreshholdLow2,'g:','LineWidth',2);hold on;
plot(TreshholdLow3,'r-.','LineWidth',2);hold on;
plot(TreshholdHigh3,'r-.','LineWidth',2);hold on;

% Check if the counts makes it shockable or not
flag = CheckIfShockable(C1,C2,C3);

if((flag == 0 && bpm<180) || flag == 1 || flag == 2)
    fprintf('Non-Shockable C1 = %d C2 = %d C3 = %d bpm = %d \n',C1,C2,C3,bpm)
end
if(flag == 3 || flag == 4)
    fprintf('Shockable C1 = %d C2 = %d C3 = %d bpm = %d \n',C1,C2,C3,bpm)
end
if((flag == 0 && bpm>180))
    fprintf('FREQUENCY Shockable C1 = %d C2 = %d C3 = %d bpm = %d \n',C1,C2,C3,bpm)
end

%% Compute 1 Sequence
close all

res = zeros(1,2100);

ComArray = ComArray423;
ATMArray = ATM423;

% Filtering ATMArray
% data = ATMArray;
% data1 = lowpass(data',30,250);
% data2 = highpass(data1,1,250);
% ATMArray = bandstop(data2, [59 61], 250);
% ATMArray = ATMArray';

for k = 1:2090
    Data2Filter = ATMArray(1 , ((k-1)*250)+1:EpochSampleLength+((k-1)*250));
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
        display('Shockable because BPM')
    end
    res(2091:2100) = res(2090);
    
end

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

count=0;
for i = 1:2100
    if(res(i) == ComArray(i))
        count = count+1;
    end
end

percentage = count/2100*100

ResReforged = zeros(1,210);
% reforge res
for index = 1:210
    m =(res(((index-1)*10)+1) + res(((index-1)*10)+2) + res(((index-1)*10)+3) + res(((index-1)*10)+4) + res(((index-1)*10)+5) + res(((index-1)*10)+6) + res(((index-1)*10)+7) + res(((index-1)*10)+8) + res(((index-1)*10)+9) + res(((index-1)*10)+10))/10;
    if(m > 80.5)
        ResReforged(index) = 83;
    else
        resReforged(index) = 78;
    end
end

temp = zeros(size(res));

for i = 1:210
    if resReforged(i) == 0
       resReforged(i) = 83; 
    end
    temp((1+((i-1)*10)):(i*10)) = resReforged(i);
end


count=0;
for i = 1:2100
    if(res(i) == ComArray(i))
        count = count+1;
    end
end

percentage = count/2100*100
[Sensitivity, Specificity] = SensitivityCalc(res,ComArray)


figure()
plot(res);hold on
plot(ComArray,'--g')
xlim([0 2100])
ylim([75 85])



%%

res418 = ComputPerc(ATM418);
res419 = ComputPerc(ATM419);
res420 = ComputPerc(ATM420);
res421 = ComputPerc(ATM421);
res422 = ComputPerc(ATM422);
res423 = ComputPerc(ATM423);
res424 = ComputPerc(ATM424);
res425 = ComputPerc(ATM425);
res426 = ComputPerc(ATM426);
res427 = ComputPerc(ATM427);
res428 = ComputPerc(ATM428);
res429 = ComputPerc(ATM429);
res430 = ComputPerc(ATM430);
res602 = ComputPerc(ATM602);
res605 = ComputPerc(ATM605);
res607 = ComputPerc(ATM607);
res609 = ComputPerc(ATM609);
res610 = ComputPerc(ATM610);
res611 = ComputPerc(ATM611);
res612 = ComputPerc(ATM612);
res614 = ComputPerc(ATM614);
res615 = ComputPerc(ATM615);


count=0;
for i = 1:2100
    if(res418(i) == ComArray418(i))
        count = count+1;
    end
    if(res419(i) == ComArray419(i))
        count = count+1;
    end
    if(res420(i) == ComArray420(i))
        count = count+1;
    end
    if(res421(i) == ComArray421(i))
        count = count+1;
    end
    if(res422(i) == ComArray422(i))
        count = count+1;
    end
    if(res423(i) == ComArray423(i))
        count = count+1;
    end
    if(res424(i) == ComArray424(i))
        count = count+1;
    end
    if(res425(i) == ComArray425(i))
        count = count+1;
    end
    if(res426(i) == ComArray426(i))
        count = count+1;
    end
    if(res427(i) == ComArray427(i))
        count = count+1;
    end
    if(res428(i) == ComArray428(i))
        count = count+1;
    end
    if(res429(i) == ComArray429(i))
        count = count+1;
    end
    if(res430(i) == ComArray430(i))
        count = count+1;
    end
    if(res602(i) == ComArray602(i))
        count = count+1;
    end
    if(res605(i) == ComArray605(i))
        count = count+1;
    end
    if(res607(i) == ComArray607(i))
        count = count+1;
    end
    if(res609(i) == ComArray609(i))
        count = count+1;
    end
    if(res610(i) == ComArray610(i))
        count = count+1;
    end
    if(res611(i) == ComArray611(i))
        count = count+1;
    end
    if(res612(i) == ComArray612(i))
        count = count+1;
    end
    if(res614(i) == ComArray614(i))
        count = count+1;
    end
    if(res615(i) == ComArray615(i))
        count = count+1;
    end
end

percentage = count/(2100*22)*100
