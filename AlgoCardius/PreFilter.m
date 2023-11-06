function [MAT] = PreFilter(NAME)

MAT = load(strcat('sample\',NAME,'.mat'));
INFO = fopen(strcat('sample\',NAME,'.info'), 'rt');

MAT = MAT.val;
fgetl(INFO);
fgetl(INFO);
fgetl(INFO);
[freqint] = sscanf(fgetl(INFO), 'Sampling frequency: %f Hz  Sampling interval: %f sec');
interval = freqint(2);
fgetl(INFO);
for i = 1:size(MAT, 1)
  [row(i), signal(i), gain(i), base(i), units(i)] = strread(fgetl(INFO),'%d%s%f%f%s','delimiter','\t');
end
fclose(INFO);
MAT(MAT==-32768) = NaN;
for i = 1:size(MAT, 1)
    MAT(i, :) = (MAT(i, :) - base(i)) / gain(i);
end

end

