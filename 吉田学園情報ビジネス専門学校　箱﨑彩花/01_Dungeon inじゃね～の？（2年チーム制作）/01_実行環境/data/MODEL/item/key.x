xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 149;
 1.42735;16.25372;-1.44033;,
 0.13229;16.46124;-1.53477;,
 0.16797;19.88912;-0.67119;,
 1.79132;19.73797;-0.49237;,
 1.66581;22.33387;1.99965;,
 0.15436;22.78366;2.04228;,
 0.16797;21.65355;5.92060;,
 1.79132;21.26727;5.69357;,
 1.66581;18.89392;8.07976;,
 0.15436;19.16732;8.43412;,
 0.16797;15.32147;7.33402;,
 1.79132;15.39279;7.12224;,
 1.42735;1.50542;-4.76257;,
 0.13229;1.10065;-4.94597;,
 0.16797;1.42745;-5.80897;,
 1.79132;1.81500;-5.58422;,
 -1.79132;13.73811;1.19726;,
 -1.42735;12.81378;4.63977;,
 -1.09840;13.91077;4.33557;,
 -1.37849;14.62207;1.68642;,
 -1.79132;15.39279;7.12224;,
 -1.66581;18.89392;8.07976;,
 -1.09840;18.58968;6.98277;,
 -1.37849;15.89542;6.24591;,
 -1.37849;20.41606;5.14649;,
 -1.79132;21.26727;5.69357;,
 -1.66581;22.33387;1.99965;,
 -1.09840;21.23687;2.30385;,
 -1.79132;19.73797;-0.49237;,
 -1.42735;16.25372;-1.44033;,
 -1.09840;16.55796;-0.34335;,
 -1.37849;19.23921;0.38615;,
 1.42735;12.81378;4.63977;,
 1.79132;13.73811;1.19726;,
 1.37849;14.62207;1.68642;,
 1.09840;13.91077;4.33557;,
 1.37849;19.23921;0.38615;,
 1.09840;16.55796;-0.34335;,
 1.79132;21.26727;5.69357;,
 1.37849;20.41606;5.14649;,
 1.09840;21.23687;2.30385;,
 1.66581;18.89392;8.07976;,
 1.79132;15.39279;7.12224;,
 1.37849;15.89542;6.24591;,
 1.09840;18.58968;6.98277;,
 1.09840;13.91077;4.33557;,
 1.37849;14.62207;1.68642;,
 0.23436;14.88531;1.83206;,
 0.19059;14.23743;4.24498;,
 1.37849;15.89542;6.24591;,
 0.23436;16.04511;5.98495;,
 0.19059;18.49907;6.65611;,
 1.09840;18.58968;6.98277;,
 1.37849;19.23921;0.38615;,
 0.23436;19.09070;0.64777;,
 0.19059;16.64857;-0.01669;,
 1.09840;16.55796;-0.34335;,
 1.09840;21.23687;2.30385;,
 1.37849;20.41606;5.14649;,
 0.23436;20.16262;4.98359;,
 0.19059;20.91021;2.39443;,
 1.09840;18.58968;6.98277;,
 0.19059;18.49907;6.65611;,
 0.13229;2.00967;-6.55267;,
 1.42735;2.37012;-6.29092;,
 0.19059;16.64857;-0.01669;,
 1.09840;16.55796;-0.34335;,
 0.13229;12.84491;4.85707;,
 1.42735;12.81378;4.63977;,
 0.19059;14.23743;4.24498;,
 1.09840;13.91077;4.33557;,
 0.19059;20.91021;2.39443;,
 1.09840;21.23687;2.30385;,
 0.13229;12.90818;1.73441;,
 1.42735;12.86045;1.66180;,
 -1.42735;12.81378;4.63977;,
 -1.79132;13.73811;1.19726;,
 -1.79132;13.17004;0.84016;,
 -1.42735;12.86045;1.66180;,
 1.79132;13.73811;1.19726;,
 1.79132;13.17004;0.84016;,
 -1.42735;16.25372;-1.44033;,
 -1.42735;13.72515;0.13344;,
 0.13229;16.46124;-1.53477;,
 1.42735;16.25372;-1.44033;,
 1.42735;13.72515;0.13344;,
 0.13229;13.81720;0.12771;,
 0.13229;6.49056;-1.89650;,
 1.42735;6.68878;-1.82996;,
 -1.79132;6.99839;-2.65159;,
 -1.42735;6.68878;-1.82996;,
 1.79132;6.99839;-2.65159;,
 -1.42735;7.55348;-3.35832;,
 1.42735;7.55348;-3.35832;,
 0.13229;7.39959;-3.50320;,
 -1.42735;2.80059;-4.02979;,
 -1.79132;3.11018;-4.85144;,
 -1.79132;1.81500;-5.58422;,
 -1.42735;1.50542;-4.76257;,
 1.42735;2.80059;-4.02979;,
 0.13229;2.44743;-4.18399;,
 1.79132;3.11018;-4.85144;,
 1.42735;3.66529;-5.55815;,
 0.13229;3.35645;-5.79070;,
 -1.42735;3.66529;-5.55815;,
 -1.42735;2.37012;-6.29092;,
 -1.42735;3.80504;-3.46150;,
 -1.79132;4.11462;-4.28315;,
 1.42735;1.97695;-0.23038;,
 0.13229;1.57008;-0.19625;,
 0.13229;0.52560;-0.78719;,
 1.42735;0.97251;-0.79867;,
 1.79132;4.11462;-4.28315;,
 1.42735;3.80504;-3.46150;,
 1.42735;4.66974;-4.98986;,
 0.13229;4.40093;-5.19976;,
 -1.42735;4.66974;-4.98986;,
 -1.42735;5.61504;-2.43745;,
 -1.79132;5.92462;-3.25910;,
 1.42735;5.61504;-2.43745;,
 0.13229;5.37403;-2.52820;,
 0.13229;3.49190;-3.59306;,
 1.79132;5.92462;-3.25910;,
 1.42735;6.47974;-3.96581;,
 0.13229;6.28306;-4.13490;,
 -1.42735;6.47974;-3.96581;,
 1.42735;4.86070;1.40116;,
 0.13229;4.56874;1.50031;,
 0.13229;3.45221;0.86860;,
 1.42735;3.78696;0.79367;,
 -1.42735;0.97251;-0.79867;,
 -1.42735;1.97695;-0.23038;,
 -1.42735;3.78696;0.79367;,
 -1.42735;4.86070;1.40116;,
 -1.66581;18.89392;8.07976;,
 -1.79132;15.39279;7.12224;,
 -1.79132;21.26727;5.69357;,
 -1.37849;14.62207;1.68642;,
 -1.09840;13.91077;4.33557;,
 -1.09840;13.91077;4.33557;,
 -1.37849;15.89542;6.24591;,
 -1.09840;18.58968;6.98277;,
 -1.37849;20.41606;5.14649;,
 -1.09840;18.58968;6.98277;,
 -1.09840;21.23687;2.30385;,
 -1.09840;21.23687;2.30385;,
 -1.37849;19.23921;0.38615;,
 -1.09840;16.55796;-0.34335;,
 -1.09840;16.55796;-0.34335;;
 
 108;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;0,3,36,37;,
 4;4,38,39,40;,
 4;41,42,43,44;,
 4;45,46,47,48;,
 4;49,50,51,52;,
 4;53,54,55,56;,
 4;57,58,59,60;,
 4;7,6,9,8;,
 4;39,38,41,44;,
 4;59,58,61,62;,
 4;21,25,24,22;,
 4;29,16,19,30;,
 4;15,14,63,64;,
 4;34,33,0,37;,
 4;65,47,46,66;,
 4;17,20,23,18;,
 4;11,10,67,68;,
 4;43,42,32,35;,
 4;69,50,49,70;,
 4;26,28,31,27;,
 4;3,2,5,4;,
 4;36,3,4,40;,
 4;71,54,53,72;,
 4;68,67,73,74;,
 4;75,76,77,78;,
 4;79,68,74,80;,
 4;76,81,82,77;,
 4;83,84,85,86;,
 4;84,79,80,85;,
 4;74,73,87,88;,
 4;78,77,89,90;,
 4;80,74,88,91;,
 4;77,82,92,89;,
 4;86,85,93,94;,
 4;85,80,91,93;,
 4;95,96,97,98;,
 4;99,100,13,12;,
 4;101,99,12,15;,
 4;102,101,15,64;,
 4;103,102,64,63;,
 4;96,104,105,97;,
 4;106,107,96,95;,
 4;108,109,110,111;,
 4;112,113,99,101;,
 4;114,112,101,102;,
 4;115,114,102,103;,
 4;107,116,104,96;,
 4;117,118,107,106;,
 4;119,120,121,113;,
 4;122,119,113,112;,
 4;123,122,112,114;,
 4;124,123,114,115;,
 4;118,125,116,107;,
 4;90,89,118,117;,
 4;126,127,128,129;,
 4;91,88,119,122;,
 4;93,91,122,123;,
 4;94,93,123,124;,
 4;89,92,125,118;,
 4;113,121,109,108;,
 4;106,95,130,131;,
 4;100,99,111,110;,
 4;99,113,108,111;,
 4;88,87,127,126;,
 4;90,117,132,133;,
 4;120,119,129,128;,
 4;119,88,126,129;,
 4;9,134,135,10;,
 4;67,10,135,75;,
 4;73,67,75,78;,
 4;87,73,78,90;,
 4;127,87,90,133;,
 4;128,127,133,132;,
 4;117,120,128,132;,
 4;121,120,117,106;,
 4;109,121,106,131;,
 4;110,109,131,130;,
 4;95,100,110,130;,
 4;13,100,95,98;,
 4;14,13,98,97;,
 4;63,14,97,105;,
 4;104,103,63,105;,
 4;116,115,103,104;,
 4;125,124,115,116;,
 4;92,94,124,125;,
 4;82,86,94,92;,
 4;81,83,86,82;,
 4;2,1,29,28;,
 4;5,2,28,26;,
 4;6,5,26,136;,
 4;9,6,136,134;,
 4;48,47,137,138;,
 4;139,140,50,69;,
 4;51,50,140,141;,
 4;142,59,62,143;,
 4;60,59,142,144;,
 4;145,146,54,71;,
 4;55,54,146,147;,
 4;137,47,65,148;;
 
 MeshMaterialList {
  1;
  108;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\key02.jpg";
   }
  }
 }
 MeshNormals {
  171;
  0.049439;-0.155144;-0.986654;,
  -0.996323;0.051733;0.068301;,
  0.269792;0.926093;0.263750;,
  -0.931780;-0.350305;0.095255;,
  0.244029;0.239414;0.939751;,
  -0.931744;-0.094920;-0.350489;,
  0.997057;0.076266;0.007840;,
  -0.997057;0.076266;0.007840;,
  -0.960696;0.267505;-0.074188;,
  -0.960696;0.074184;0.267506;,
  0.741256;0.646739;-0.179634;,
  0.741622;0.179812;0.646270;,
  0.708304;-0.681523;0.183933;,
  0.707051;-0.183244;-0.683008;,
  -0.895929;-0.385172;-0.221256;,
  0.278035;0.827732;0.487398;,
  0.646457;-0.659248;-0.384037;,
  -0.616502;-0.680129;-0.396674;,
  -0.645183;0.665705;0.374935;,
  -0.993814;0.095404;0.056845;,
  0.993814;0.095404;0.056845;,
  0.674123;0.643532;0.362527;,
  -0.630635;0.370766;-0.681786;,
  -0.911059;0.181316;-0.370266;,
  0.137918;-0.497856;0.856223;,
  0.660104;0.358688;-0.660004;,
  -0.630683;-0.394501;0.668287;,
  -0.911119;-0.224088;0.345901;,
  0.144976;0.478829;-0.865855;,
  0.660150;-0.381970;0.646761;,
  -0.032562;-0.999308;-0.017955;,
  -0.935477;-0.247603;0.252143;,
  -0.995887;-0.081007;-0.040574;,
  0.995887;-0.081007;-0.040574;,
  -0.939809;0.094895;-0.328260;,
  -0.028665;-0.530133;-0.847430;,
  0.290691;-0.914403;-0.281720;,
  -0.922138;-0.190500;0.336707;,
  -0.999991;-0.002070;0.003659;,
  0.297607;-0.832016;-0.468167;,
  -0.925358;0.186675;-0.329947;,
  0.292143;-0.715018;-0.635139;,
  -0.999991;-0.002070;0.003658;,
  -0.964935;-0.129256;0.228459;,
  0.030637;-0.492193;0.869947;,
  0.999991;-0.002070;0.003658;,
  0.925358;0.186675;-0.329948;,
  -0.925358;0.186675;-0.329948;,
  -0.999991;-0.002070;0.003659;,
  -0.964935;-0.129256;0.228459;,
  0.964935;-0.129256;0.228459;,
  0.999991;-0.002070;0.003659;,
  0.925358;0.186675;-0.329947;,
  -0.925358;0.186675;-0.329947;,
  -0.999991;-0.002070;0.003659;,
  -0.964935;-0.129256;0.228459;,
  0.030637;-0.492192;0.869947;,
  0.999991;-0.002070;0.003659;,
  0.925358;0.186675;-0.329947;,
  -0.925358;0.186675;-0.329947;,
  -0.999991;-0.002070;0.003659;,
  -0.964935;-0.129256;0.228459;,
  0.030637;-0.492192;0.869947;,
  0.999991;-0.002070;0.003659;,
  0.038825;0.492053;-0.869699;,
  -1.000000;0.000000;0.000000;,
  0.174908;-0.484833;0.856939;,
  0.174908;-0.484834;0.856938;,
  0.020486;0.248133;0.968509;,
  0.011661;-0.502292;0.864619;,
  0.003627;-0.926794;0.375551;,
  -0.002761;-0.999835;-0.017965;,
  0.002598;-0.492422;0.870353;,
  0.014678;-0.492372;0.870261;,
  0.002598;-0.492422;0.870353;,
  0.014678;-0.492371;0.870262;,
  0.002598;-0.492422;0.870353;,
  0.023599;-0.952164;-0.304675;,
  0.024189;-0.871200;-0.490331;,
  0.023786;-0.754447;-0.655930;,
  0.003291;0.492421;-0.870351;,
  0.003291;0.492421;-0.870351;,
  0.003291;0.492421;-0.870351;,
  0.003291;0.492421;-0.870351;,
  -0.002431;-0.530349;-0.847776;,
  0.004123;-0.154587;-0.987971;,
  0.012249;0.484260;-0.874838;,
  0.022402;0.961287;0.274638;,
  0.023134;0.861508;0.507217;,
  0.040272;0.870951;0.489717;,
  0.039211;0.961337;0.272567;,
  0.040271;0.493455;-0.868838;,
  0.039125;0.276760;-0.960142;,
  0.040297;-0.861743;-0.505741;,
  0.038860;-0.956396;-0.289476;,
  0.040271;-0.492380;0.869448;,
  0.039149;-0.275573;0.960483;,
  0.996323;0.051733;0.068301;,
  0.911119;-0.224088;0.345901;,
  0.931780;-0.350305;0.095255;,
  0.895929;-0.385172;-0.221256;,
  0.931744;-0.094920;-0.350489;,
  0.911059;0.181316;-0.370266;,
  0.039486;-0.718883;-0.694009;,
  0.039106;0.732408;0.679742;,
  0.043457;-0.926186;0.374554;,
  0.039190;0.682885;-0.729474;,
  0.013668;0.689868;-0.723806;,
  0.161302;0.681260;-0.714050;,
  0.039165;-0.681967;0.730333;,
  0.935477;-0.247603;0.252143;,
  0.939809;0.094895;-0.328260;,
  0.964935;-0.129256;0.228459;,
  0.003291;0.492421;-0.870351;,
  0.038824;0.492052;-0.869699;,
  0.964935;-0.129256;0.228459;,
  0.922138;-0.190500;0.336707;,
  0.999991;-0.002070;0.003659;,
  0.925358;0.186675;-0.329947;,
  0.038825;0.492052;-0.869700;,
  0.038825;0.492052;-0.869700;,
  0.003291;0.492420;-0.870351;,
  0.038825;0.492052;-0.869699;,
  0.964935;-0.129256;0.228459;,
  0.038825;0.492052;-0.869699;,
  -0.252053;0.842255;0.476525;,
  -0.020900;0.870166;0.492316;,
  0.023383;-0.870118;-0.492289;,
  0.283810;-0.834567;-0.472175;,
  1.000000;0.000000;-0.000000;,
  -0.156558;0.859623;0.486351;,
  -0.013167;0.870280;0.492381;,
  0.016141;-0.870242;-0.492360;,
  0.192794;-0.854027;-0.483186;,
  -0.128697;-0.265514;0.955479;,
  -0.114749;-0.498678;0.859158;,
  -0.036195;-0.925932;0.375952;,
  0.027043;-0.999473;-0.017958;,
  -0.025443;-0.492264;0.870074;,
  0.130498;0.862913;0.488213;,
  -0.145932;-0.487153;0.861037;,
  -0.161021;-0.858998;-0.485998;,
  -0.025443;-0.492264;0.870074;,
  0.211391;0.850687;0.481296;,
  -0.145932;-0.487152;0.861038;,
  -0.238668;-0.845203;-0.478193;,
  -0.025444;-0.492264;0.870074;,
  -0.245224;-0.920140;-0.305301;,
  -0.250111;-0.843711;-0.474970;,
  -0.246331;-0.738045;-0.628180;,
  -0.032247;0.492167;-0.869903;,
  -0.032246;0.492167;-0.869903;,
  -0.032247;0.492167;-0.869903;,
  -0.032246;0.492168;-0.869903;,
  -0.032246;0.492168;-0.869903;,
  -0.032246;0.492168;-0.869903;,
  -0.041185;-0.153712;-0.987257;,
  0.023805;-0.530200;-0.847538;,
  -0.120661;0.481109;-0.868318;,
  -0.134267;0.683323;-0.717665;,
  -0.226390;0.936343;0.268345;,
  -0.233381;0.837971;0.493292;,
  -0.226292;0.689047;0.688480;,
  -0.198091;0.944125;0.263417;,
  -0.197969;0.672863;-0.712786;,
  -0.197578;0.267643;-0.943043;,
  -0.199733;-0.701896;-0.683703;,
  -0.195996;-0.939641;-0.280464;,
  -0.197819;-0.671969;0.713671;,
  -0.197724;-0.266446;0.943351;,
  -0.197466;0.715806;0.669798;;
  108;
  4;0,85,86,28;,
  4;2,87,88,15;,
  4;4,68,69,24;,
  4;36,77,78,39;,
  4;19,7,8,18;,
  4;23,5,5,22;,
  4;17,14,3,3;,
  4;27,1,9,26;,
  4;6,20,21,10;,
  4;97,98,29,11;,
  4;99,100,16,12;,
  4;101,102,25,13;,
  4;10,21,89,90;,
  4;25,91,92,13;,
  4;29,95,96,11;,
  4;12,16,93,94;,
  4;15,88,68,4;,
  4;16,100,101,13;,
  4;93,16,13,103;,
  4;5,14,17,5;,
  4;1,19,18,9;,
  4;39,78,79,41;,
  4;21,20,97,11;,
  4;104,89,21,11;,
  4;7,23,22,8;,
  4;24,69,70,105;,
  4;25,102,6,10;,
  4;106,91,25,10;,
  4;3,27,26,3;,
  4;28,86,107,108;,
  4;29,98,99,12;,
  4;109,95,29,12;,
  4;105,70,71,30;,
  4;7,19,32,31;,
  4;20,6,110,33;,
  4;19,1,34,32;,
  4;85,0,35,84;,
  4;97,20,33,111;,
  4;62,72,72,62;,
  4;31,32,60,61;,
  4;33,110,112,63;,
  4;32,34,53,60;,
  4;113,114,64,83;,
  4;111,33,63,52;,
  4;43,42,38,37;,
  4;44,76,76,44;,
  4;45,115,116,117;,
  4;46,45,117,118;,
  4;80,119,120,121;,
  4;42,47,40,38;,
  4;49,48,42,43;,
  4;66,75,75,66;,
  4;51,50,115,45;,
  4;52,51,45,46;,
  4;81,122,119,80;,
  4;48,53,47,42;,
  4;55,54,48,49;,
  4;56,74,74,56;,
  4;57,123,50,51;,
  4;58,57,51,52;,
  4;82,124,122,81;,
  4;54,59,53,48;,
  4;61,60,54,55;,
  4;67,73,73,67;,
  4;63,112,123,57;,
  4;52,63,57,58;,
  4;83,64,124,82;,
  4;60,53,59,54;,
  4;125,126,126,125;,
  4;49,43,65,65;,
  4;127,128,128,127;,
  4;115,50,129,129;,
  4;130,131,131,130;,
  4;61,55,65,65;,
  4;132,133,133,132;,
  4;123,112,129,129;,
  4;68,134,135,69;,
  4;70,69,135,136;,
  4;71,70,136,137;,
  4;72,72,138,138;,
  4;131,131,139,139;,
  4;73,73,140,140;,
  4;141,132,132,141;,
  4;74,74,142,142;,
  4;126,126,143,143;,
  4;75,75,144,144;,
  4;145,127,127,145;,
  4;76,76,146,146;,
  4;78,77,147,148;,
  4;79,78,148,149;,
  4;150,80,121,151;,
  4;152,81,80,150;,
  4;153,82,81,152;,
  4;154,83,82,153;,
  4;155,113,83,154;,
  4;156,85,84,157;,
  4;86,85,156,158;,
  4;107,86,158,159;,
  4;88,87,160,161;,
  4;68,88,161,162;,
  4;90,89,18,163;,
  4;164,22,91,106;,
  4;92,91,22,165;,
  4;17,93,103,166;,
  4;94,93,17,167;,
  4;168,26,95,109;,
  4;96,95,26,169;,
  4;18,89,104,170;;
 }
 MeshTextureCoords {
  149;
  0.375000;1.000000;,
  0.488340;1.000000;,
  0.488340;0.874820;,
  0.375000;0.874820;,
  0.375000;0.750000;,
  0.488340;0.750000;,
  0.488340;0.617950;,
  0.375000;0.617950;,
  0.375000;0.500000;,
  0.488340;0.500000;,
  0.488340;0.374260;,
  0.375000;0.374260;,
  0.375000;0.250000;,
  0.488340;0.250000;,
  0.488340;0.126180;,
  0.375000;0.126180;,
  0.751180;1.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.751180;1.000000;,
  0.875000;0.875740;,
  0.875000;0.750000;,
  0.875000;0.750000;,
  0.875000;0.875740;,
  0.757050;0.750000;,
  0.757050;0.750000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.874820;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.874820;,
  0.125000;1.000000;,
  0.248820;1.000000;,
  0.248820;1.000000;,
  0.125000;1.000000;,
  0.375000;0.874820;,
  0.375000;1.000000;,
  0.242950;0.750000;,
  0.242950;0.750000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.125000;0.875740;,
  0.125000;0.875740;,
  0.125000;0.750000;,
  0.000000;1.000000;,
  0.495260;1.000000;,
  0.495260;0.585780;,
  0.000000;0.585780;,
  0.497060;0.000000;,
  0.497060;0.414220;,
  1.000000;0.414220;,
  1.000000;0.000000;,
  0.499270;0.000000;,
  0.499270;0.414220;,
  1.000000;0.414220;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.528210;1.000000;,
  0.528210;0.585780;,
  0.000000;0.585780;,
  1.000000;1.000000;,
  1.000000;0.585780;,
  0.488340;0.000000;,
  0.375000;0.000000;,
  1.000000;0.585780;,
  1.000000;1.000000;,
  0.488340;0.250000;,
  0.375000;0.250000;,
  0.000000;0.414220;,
  0.000000;0.000000;,
  0.000000;0.414220;,
  0.000000;0.000000;,
  0.488340;0.250000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.126180;,
  0.625000;0.126180;,
  0.625000;0.250000;,
  0.375000;0.126180;,
  0.375000;0.126180;,
  0.625000;0.000000;,
  0.625000;0.000000;,
  0.488340;0.000000;,
  0.375000;0.000000;,
  0.375000;0.000000;,
  0.488340;0.000000;,
  0.488340;0.250000;,
  0.375000;0.250000;,
  0.625000;0.126180;,
  0.625000;0.250000;,
  0.375000;0.126180;,
  0.625000;0.000000;,
  0.375000;0.000000;,
  0.488340;0.000000;,
  0.625000;0.250000;,
  0.625000;0.126180;,
  0.625000;0.126180;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.488340;0.250000;,
  0.375000;0.126180;,
  0.375000;0.000000;,
  0.488340;0.000000;,
  0.625000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.126180;,
  0.375000;0.250000;,
  0.488340;0.250000;,
  0.488340;0.250000;,
  0.375000;0.250000;,
  0.375000;0.126180;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.488340;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.126180;,
  0.375000;0.250000;,
  0.488340;0.250000;,
  0.488340;0.250000;,
  0.375000;0.126180;,
  0.375000;0.000000;,
  0.488340;0.000000;,
  0.625000;0.000000;,
  0.375000;0.250000;,
  0.488340;0.250000;,
  0.488340;0.250000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.500000;,
  0.625000;0.374260;,
  0.625000;0.617950;,
  0.495260;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.497060;1.000000;,
  1.000000;1.000000;,
  0.528210;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.499270;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}
