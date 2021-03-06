clc;
clear functions;

NAMES = { ...
  'FresnelCS', ...
  'XY_to_angle', ...
  'CircleArcMexWrapper', ...
  'BiarcMexWrapper', ...
  'BiarcListMexWrapper', ...
  'LineSegmentMexWrapper', ...
  'PolyLineMexWrapper', ...
  'Triangle2DMexWrapper', ...
  'ClothoidCurveMexWrapper', ...
  'ClothoidListMexWrapper', ...
  'ClothoidSplineG2MexWrapper', ...
  'TriTriOverlap'
};

LIB_NAMES = { ...
  'G2lib', ...
  'G2lib_intersect', ...
  'AABBtree', ...
  'Line',...
  'PolyLine', ...
  'Circle', ...
  'Biarc', ...
  'BiarcList', ...
  'Clothoid', ...
  'ClothoidList', ...
  'ClothoidDistance', ...
  'ClothoidG2', ...
  'Fresnel', ...
  'Triangle2D', ...
};

LIB_NAMES2 = { ...
  'PolynomialRoots-1-Quadratic', ...
  'PolynomialRoots-2-Cubic', ...
  'PolynomialRoots-Utils', ...
};

MROOT = matlabroot;

LIB_SRCS = '';
LIB_OBJS = '';
for k=1:length(LIB_NAMES)
  LIB_SRCS = [ LIB_SRCS, ' ../src/', LIB_NAMES{k}, '.cc' ];
  if isunix
    LIB_OBJS = [ LIB_OBJS, LIB_NAMES{k}, '.o ' ];
  elseif ispc
    LIB_OBJS = [ LIB_OBJS, LIB_NAMES{k}, '.obj ' ];
  end
end
for k=1:length(LIB_NAMES2)
  LIB_SRCS = [ LIB_SRCS, ' ../submodules/quarticRootsFlocke/src/', LIB_NAMES2{k}, '.cc' ];
  if isunix
    LIB_OBJS = [ LIB_OBJS, LIB_NAMES2{k}, '.o ' ];
  elseif ispc
    LIB_OBJS = [ LIB_OBJS, LIB_NAMES2{k}, '.obj ' ];
  end
end

[~,mexLoaded] = inmem('-completenames');

disp('---------------------------------------------------------');

CMD = 'mex -c -largeArrayDims -I../src -I../submodules/quarticRootsFlocke/src ';
if isunix
  CMD = [CMD, 'CXXFLAGS="\$CXXFLAGS -Wall -O2 -g" '];
elseif ispc
end
CMD = [ CMD, LIB_SRCS ];

disp(CMD);
eval(CMD);

for k=1:length(NAMES)
  N=NAMES{k};
  disp('---------------------------------------------------------');
  fprintf(1,'Compiling: %s\n',N);

  CMD = [ 'while mislocked(''' N '''); munlock(''' N '''); end;'];
  eval(CMD);

  CMD = [ 'mex -I../src -output ../matlab/', N ];
  CMD = [ CMD, ' -largeArrayDims ../src_mex/mex_', N ];
  CMD = [ CMD, '.cc ', LIB_OBJS ];

  if ismac
    CMD = [CMD, ' CXXFLAGS="\$CXXFLAGS -Wall -O2 -g"'];
  elseif isunix
    % Workaround for MATLAB 2020 that force dynamic link with old libstdc++
    % solution: link with static libstdc++
    % ARCH  = computer('arch');
    % PATH1 = [MROOT, '/bin/', ARCH];
    % PATH2 = [MROOT, '/extern/bin/', ARCH];
    CMD = [ CMD, ...
      ' CXXFLAGS="\$CXXFLAGS -Wall -O2 -g"' ...
      ' LDFLAGS="\$LDFLAGS -static-libgcc -static-libstdc++"' ...
      ' LINKLIBS="-L\$MATLABROOT/bin/\$ARCH -L\$MATLABROOT/extern/bin/\$ARCH -lMatlabDataArray -lmx -lmex -lmat -lm "' ...
    ];
  elseif ispc
  end

  disp(CMD);
  eval(CMD);
end

for k=1:length(LIB_NAMES)
  if isunix
    delete([ LIB_NAMES{k}, '.o' ]);
  elseif ispc
    delete([ LIB_NAMES{k}, '.obj' ]);
  end
end

disp('----------------------- DONE ----------------------------');
