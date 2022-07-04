function generate_ETC()

outputFile = "../include/etc_curve.h";
templateFile = "template.h";

% Max Motor Torque is 230, this is also for limited time, and likely
% unreachable.

f = @(x) x*10;
%f = @(x) x;

request = 0:1:2300;
output = f(request);

%plot(request, output);

TableSize = size(request);
TableSize = TableSize(2);

Data = "";
cnt = 0;
for d = output
    if cnt == (TableSize-1)
        Data = sprintf("%s\n0x%X", Data, d);
    elseif (mod(cnt, 5) == 0)
        Data = sprintf("%s\n0x%X, ", Data, d);
    else
        Data = sprintf("%s0x%X, ", Data, d);
    end
    cnt = cnt + 1;
end

buffer = "";
fd = fopen (templateFile, 'r');

% Populate buffer with template file
while ~feof(fd)
    % Regex Parse
    line = fgetl(fd);

    if contains(line, "%<TABLE_SIZE>")
        line = strrep(line, "%<TABLE_SIZE>", num2str(TableSize));
    elseif contains(line, "%<DATA>")
        line = strrep(line, "%<DATA>", Data);
    elseif contains(line, "%<DATE_TIME>")
        line = strrep(line, "%<DATE_TIME>", string(datetime));
    end

    buffer = sprintf("%s%s\n", buffer, line);
end

fclose(fd);

% Write buffer to file
fd = fopen(outputFile, 'w');
fprintf(fd, buffer);
fclose(fd);

end