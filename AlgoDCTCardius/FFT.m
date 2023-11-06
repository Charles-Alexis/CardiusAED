clc
clear all
close all

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

pos =25;
TestData = ATM426(1,1+(2500*pos):EpochSampleLength+(2500*pos));
Data = TestData;
DataDCT=dct(Data);
na=std(DataDCT);

for k=1:length(DataDCT)
   if abs(DataDCT(k)) > na
       New_DataDCT(k)=DataDCT(k);
   else
       New_DataDCT(k)=0;
   end
end
New_Data=idct(New_DataDCT);

figure(3)
subplot(2,2,3)
plot(DataDCT)
title('Contenu fréquentielle avant filtrage')
xlabel('Fréquence(Hz)')
ylim([-2 2])
xlim([0 1000])
subplot(2,2,4)
plot(New_DataDCT)
title('Contenu fréquentielle après filtrage')
xlabel('Fréquence(Hz)')
ylim([-2 2])
xlim([0 1000])
subplot(2,2,1)
plot(Data)
title('Échantillon dans le domaine temporel avant filtrage')
xlabel('Temps(s)')
subplot(2,2,2)
plot(New_Data)
title('Échantillon dans le domaine temporel après filtrage')
xlabel('Temps(s)')
%création du signal bipolaire à polarité alternées
sn=New_Data;
wn=ones(1,length(sn));
wn=(-1).^(0:length(wn)-1);
wn=wn.*max(sn);

%Création du signal zn et calcul du ZCR
zn=sn+wn;
somme=0;
for i=2:length(zn)
    somme=somme+abs(sign(zn(i))-sign(zn(i-1)));
end
ZCR=(1/length(zn))*somme;


%%

sn=New_Data;
pn=ones(1,length(sn));
pn=(-1).^(0:length(pn)-1);
pn=pn.*-1;
ATMArray = ATM426;
figure(1)
hold on
for k = 1:2090
    Data = ATMArray(1 , ((k-1)*250)+1:EpochSampleLength+((k-1)*250));
    DataDCT=dct(Data);
    na=std(DataDCT);
    
    for i=1:length(DataDCT)
       if abs(DataDCT(i)) > na
           New_DataDCT(i)=DataDCT(i);
       else
           New_DataDCT(i)=0;
       end
    end
   
    sn=idct(New_DataDCT);
    wn=pn.*na; %;
    zn=sn+wn;
    somme=0;
    
    for i=2:length(zn)-1
        somme=somme+abs(sign(zn(i))-sign(zn(i-1)));
    end
    ZCR(k)=(1/(length(zn)))*somme;
    
    if ComArray426(k) ==78
        plot(k,ZCR(k),'b*')
    else
        plot(k,ZCR(k),'ro')
    end
    
    
%     somme=0;
%     for i=2:length(sn)
%         somme=somme+abs(sign(sn(i))-sign(sn(i-1)));
%     end
%     
%     ZCR_2(k)=(1/length(zn))*somme;
end
hold off
% figure(1)
% plot(ZCR,'*')
% 
% figure(2)
% plot(ZCR_2,'*')