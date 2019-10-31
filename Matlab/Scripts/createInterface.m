function createInterface(Name, Description, Unit, DataType, Scale, Dimension, StorageClass ...
   , PhysicalMin, PhysicalMax, Owner, Path, Offset) %#ok<INUSL>
%
%    function createInterface(Name, Description, Unit, DataType, Scale, Dimension, StorageClass ...
%        , PhysicalMin, PhysicalMax, Owner, Path, Offset)
%
%  Creates an I/O signal in the base workspace.
%
%% check input
cStorageClassAllowed = {'ImportedExtern' 'ExportedGlobal' 'ImportedExternPointer' 'GetSet' 'ImportedDefine' 'Define' 'ImportFromFile'};
if ~any(strcmp(StorageClass, cStorageClassAllowed))
    error('Bad StorageClass, only %s allowed, found "%s".' ...
    ,cStorageClassAllowed{:}, StorageClass);
end
% be backwards compatible to old no-offset calls of this function
if nargin < 12
   Offset = 0;
end

% calling stack and dependency list
getCurSys = curSys;
ST = dbstack();

if length(ST) < 2
% make_cal_param has been run from the command line
   caller = 'command line';
   line = 0;
else
    % regular call
    filePath = which(ST(2,1).name);
    caller = ST(2).file;
    line = ST(2).line;
end

%% storage class handling
V = Simulink.Signal;
if strcmp(StorageClass, 'Define')
    V.RTWInfo.StorageClass = 'Custom';
    V.RTWInfo.CustomStorageClass = 'ImportFromFile';
elseif strcmp(StorageClass,'ImportedDefine')
    V.RTWInfo.StorageClass = 'Custom';
    V.RTWInfo.CustomStorageClass = 'ImportFromFile';
elseif strcmp(StorageClass,'GetSet')
    V.RTWInfo.StorageClass = 'Custom';
    V.RTWInfo.CustomStorageClass = 'GetSet';
elseif strcmp(StorageClass, 'ImportFromFile')
    V.RTWInfo.StorageClass = 'Custom';
    V.RTWInfo.CustomStorageClass = 'ImportFromFile';
else
    V.RTWInfo.StorageClass = StorageClass;
end


[signed, numBits] = getParTypeInfo( DataType );
slope = Scale;
% make slope string in terms of fraction length or slope itself, depending on being a whole power of two
slopeStr = gft_mlfxp_mkscalingstring(slope);

%% datatype handling
if ~isa(DataType, 'Simulink.NumericType')
   if strfind(DataType,'boolean')
        V.DataType = 'boolean';
        Unit = 'boolean';
   elseif strfind(DataType,'int')
        V.DataType = ['fixdt(' num2str(signed) ',' num2str(numBits) ',' slopeStr ',' num2str(Offset) ')'];
   elseif strncmp('Enum:', DataType, 5)
        V.DataType = DataType;
   else
   disp(['Unsupported DataType for Parameter: ' Name]);
   end
else

% uint, sint, sfix etc. are legacy code. Use fixdt instead!
% a = fixdt(Signed, WordLength, TotalSlope, Bias)


% Check Numeric type of uint and sint
% Here the fractional length must be zero, otherwise show a warning
    if strcmp(DataType.DataTypeMode, 'Fixed-point: binary point scaling')
        slopeStrArr = strsplit(slopeStr, '^');
        if strcmp(slopeStrArr{2}, '0') == 0
        disp(['Warning: "', Name, '" is of type uint or sint but fraction length is ', slopeStrArr{2}]);
        end
    end

    V.DataType = ['fixdt(' num2str(signed) ',' num2str(numBits) ',' slopeStr ',' num2str(Offset) ')'];

end

%% validity checks
% check if range limits are explicit values, means numeric types, if yes they are returned unchecked.
[checkvMin, checkvMax] = checkMinMax(Name, PhysicalMin, PhysicalMax, DataType, signed, numBits, slope, Offset);

if ~strncmp('Enum:', DataType, 5)
    V.Max = checkvMax;
    V.Min = checkvMin;
end

if strfind(caller, getCurSys)
    if~strncmp(StorageClass, 'ImportedExtern', 14)
    %check the validility of the Description parameter
        if isempty(regexpi(strtrim(Description), '\w*[A-Za-z0-9]\w*[^na][^n\/?a]', 'once')) ...
            || strcmp(Description, 'tbd')
            fprintf(['Warning (<a href="matlab: opentoline(''%s'', %i);">%s:%i</a>): ' ...
            'The description ''%s'' is not valid for %s\n'], ...
            filePath, line, caller, line, Description, Name);
        end

        %check the validility of the Unit parameter
        switch strtrim(lower(Unit))
        case {'na', 'n/a'}
            fprintf(['Warning (<a href="matlab: opentoline(''%s'', %i);">%s:%i</a>): ' ...
                    'Please replace the Unit ''%s'' with ''-'' for %s\n'], ...
                        filePath, line, caller, line, strtrim(Unit), Name);
        case ''
            fprintf(['Warning (<a href="matlab: opentoline(''%s'', %i);">%s:%i</a>): ' ...
            'The unit is empty for %s\n'], ...
            filePath, line, caller, line, Name);
        end
    end
end

%% populate the parameter
V.DocUnits = Unit;

V.Dimensions = Dimension;
V.Description = Description;

assignin('base', Name, V);

%% get global variable for showing the warnings
function getCurSys = curSys
global currentSys
getCurSys = currentSys;

