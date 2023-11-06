function [bpm] = CountBPM(Data)

    for i = 1:30
        
        MaxValue = 0.45 * max(Data) / i;
        MinValue = 0.45 * min(Data) / i;
        p1=0;
        p2=0;
        c1=0;
        c2=0;
        
        %Peak 1
        for j =1:2500
            if(j==2500)
                p1 = 0;
                break
            end
            if(Data(j)< MinValue)
                p1 = j+25;
                break
            end
        end
        
        %Peak 2
        for j =p1:2500
            if(j==2500 || p1 == 0)
                c1 = 0;
                break
            end
            
            if(Data(j)>MaxValue)
                d1 = j;
                
                for k = 1:250
                    if((j+k-1)>2500)
                        break
                    end
                    if(Data(j+k-1) < Data(j))
                        max1 = max(Data(j:(j+k-1)));
                        c1 = find(Data(j:(j+k-1))==max1) + j;
                        break
                    end
                end
                
                break
            end
        end
        
        %Peak 3
        for j =c1:2500
            if(j==2500 || c1 == 0)
                p2 = 0;
                break
            end
            if(Data(j)< MinValue)
                p2 = j+25;
                break
            end
        end
        
        %Peak 4
        for j =p2:2500
            if(j==2500 ||p2 == 0)
                c2 = 0;
                break
            if(Data(j)>MaxValue)
                d2 = j;
                for k = 1:250
                    if(Data(j+k-1) < Data(j))
                        max1 = max(Data(j:(j+k-1)));
                        c2 = find(Data(j:(j+k-1))==max1) + j;
                        break
                    end
                end
                
                break
            end
        end
        
        bpm = 60/((c2-c1)*0.004);
    end

end

