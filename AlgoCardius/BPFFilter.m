function [FilteredData] = BPFFilter(Data2Filter)

    CoefU  = [(1/16) 0 (1/16)];
    CoefY  = [1 (14/8) (7/8)];
    FilteredData = zeros(1,2500);
    Input1=0;
    Input2=0;
    Input3=0;

    Output1 = 0;
    Output2 = 0;
    Output3 = 0;

    for i = 1:2500
        Input3 = Input2;
        Input2 = Input1;
        Input1 = Data2Filter(i);

        Output3 = Output2;
        Output2 = Output1;
        Output1 = (CoefY(2)*Output2)-((CoefY(3))*Output3)+((CoefU(1))*(Input1-Input3));
        FilteredData(i) = Output1;
    end

end

