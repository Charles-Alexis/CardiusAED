function [res] = Data2Txt(Data, FileName)
    Data2Filter = Data(1,:);
    FilteredResult = BPFFilter(Data2Filter,length(Data2Filter))
    res = Data2Filter;
    
    
    fileID = fopen(FileName,'w');
    fprintf(fileID,'%f\n',res);
    fclose(fileID);


end