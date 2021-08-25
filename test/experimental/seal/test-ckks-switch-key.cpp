// Copyright (C) 2020-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include <gtest/gtest.h>

#include <memory>
#include <random>
#include <vector>

#include "hexl/experimental/seal/ckks-switch-key.hpp"
#include "hexl/logging/logging.hpp"
#include "hexl/number-theory/number-theory.hpp"
#include "test-util.hpp"

namespace intel {
namespace hexl {

TEST(CkksSwitchKey, small) {
  std::vector<std::vector<uint64_t>> key_vector{
      {31369078234928549,   167410544543601533,  30295063465117864,
       1029113708974659001, 350455048150478228,  1069609725127969255,
       1095239690300936370, 559542970999798226,  1113118014604834368,
       80445551769419656,   545362596095709695,  485637139473951465,
       116020618343478474,  801934249052842378,  970219816143916801,
       1058452012721328932, 870915869136302447,  402386581348438533,
       1065588400627367011, 157588820834882581,  146068553477328742,
       1042667453166545590, 595073719978649885,  823077372512526233,
       995530245730222941,  812007683370049732,  337703844157246839,
       808682978399161429,  913647413305744800,  63500453384227259,
       975239036429266878,  250079223903275949,  896761180441348710,
       439128758341811319,  772988782437626043,  909591374183886736,
       351605775904614399,  245669369252826903,  99838041204989119,
       997636640184350688,  1029368738428779874, 806642759538225504,
       71973668581320190,   722420941300790331,  682444628450766747,
       1006658105772622187, 392185171627884168,  279897649381283504,
       607126579845444596,  523677329583686245,  876689480851459405,
       870443905693074434,  346704991372895838,  391139030755466109,
       769939737600349745,  1114191753334760295, 437508080522107209,
       37088441641534144,   377795713357953884,  278835516193096942,
       770965498199333161,  416821214609044034,  636181616064335660,
       257162050628395041,  926326292454275307,  1143847307170567958,
       1023880313549978602, 335820784739027926,  837583550898488850,
       714014692066771197,  663272924403084028,  894944803742088035,
       109914415847555142,  791292420202543959,  348244536989110469,
       688053345118295652,  335936743801514204,  732834909716799754,
       207609272137584237,  271671532013193649,  407722526351389064,
       82911897751260137,   393611688972488922,  376878436971945487,
       846472159350520059,  337000750558850773,  268545460951708300,
       459013000042831212,  691036738168843143,  3555741998349423,
       349347154001009930,  560381288282565540,  759808009117113298,
       522637499639226850,  1126179821426876151, 1091630265319001783},
      {89873054755123330,   326616096109446307,  520343486925087077,
       653174129747721535,  1119250873759085069, 708940711689947363,
       201586746120355067,  983619136387357185,  737478992366508820,
       838369153278707906,  451286807005268211,  564041546714935251,
       768108857663159231,  416015029409745206,  539180391289417127,
       586340814781173694,  517957769458336870,  516874973338334751,
       801043703806519925,  927409302171519785,  814111599836437487,
       810502477294356609,  810983291860630293,  249148390683103435,
       462537862019276347,  1114751529344521012, 467191879477073117,
       975915555577328102,  1041205056817057596, 685177182464908962,
       149718950486724175,  1068149629731891456, 896761180441348710,
       439128758341811319,  772988782437626043,  909591374183886736,
       351605775904614399,  245669369252826903,  99838041204989119,
       997636640184350688,  1029368738428779874, 806642759538225504,
       71973668581320190,   722420941300790331,  682444628450766747,
       1006658105772622187, 392185171627884168,  279897649381283504,
       607126579845444596,  523677329583686245,  876689480851459405,
       870443905693074434,  346704991372895838,  391139030755466109,
       769939737600349745,  1114191753334760295, 437508080522107209,
       37088441641534144,   377795713357953884,  278835516193096942,
       770965498199333161,  416821214609044034,  636181616064335660,
       257162050628395041,  926326292454275307,  1143847307170567958,
       1023880313549978602, 335820784739027926,  837583550898488850,
       714014692066771197,  663272924403084028,  894944803742088035,
       109914415847555142,  791292420202543959,  348244536989110469,
       688053345118295652,  335936743801514204,  732834909716799754,
       207609272137584237,  271671532013193649,  407722526351389064,
       82911897751260137,   393611688972488922,  376878436971945487,
       846472159350520059,  337000750558850773,  268545460951708300,
       459013000042831212,  691036738168843143,  3555741998349423,
       349347154001009930,  560381288282565540,  759808009117113298,
       522637499639226850,  1126179821426876151, 1091630265319001783}};

  size_t coeff_count = 16;
  std::vector<uint64_t> moduli{1152921504606844417, 1152921504606844513,
                               1152921504606845473};

  std::vector<uint64_t> modswitch_factors{1047018677005647534,
                                          1036428394245527932};
  size_t decomp_modulus_size = 2;
  size_t key_modulus_size = 3;
  size_t rns_modulus_size = 3;
  size_t key_component_count = 2;

  std::vector<const uint64_t*> hexl_key_vectors;
  for (const auto& each_key : key_vector) {
    hexl_key_vectors.push_back(&each_key.data()[0]);
  }

  std::vector<uint64_t> input{
      309939064110586901,  451312085004349512,  882903116694970497,
      1093749375736930196, 411821859017025404,  1121873370851731682,
      670590992712042547,  872840509717262120,  954337535848042283,
      718278395972892277,  1111208627088419160, 824743622506129167,
      1001558143368137981, 96920090003600788,   949961333638731679,
      923858185179999823,  1113848237884615331, 959412567469145467,
      859210277205990667,  822430581217081861,  480267076233076947,
      225243686971827410,  730689801764347033,  528298360406900389,
      138501526699581979,  1092967882971961295, 580905959433010662,
      351821126548194417,  25169770702816533,   269338260100095445,
      989908645560307191,  1083232529988885462, 199743077891248337,
      45350898252201920,   520413747874700379,  798236191365674310,
      306057106308510612,  915485980916714257,  173706584180453182,
      818593070995232781,  439133138449531358,  703831179776447716,
      428342677657435367,  76119365963542295,   746684297130764143,
      879503424958138925,  913944067499620531,  883572924636256248,
      128708740540900462,  1089491495533625982, 448517149883349853,
      1052824173420271503, 63620226327680354,   551552858385324721,
      450255932106529562,  208762778846281448,  321384903649655207,
      410032640763252152,  244794820679959515,  61689117770931594,
      158745490550837326,  767620575722239071,  937492088261647801,
      216611853169055339,  754456001494305689,  1103969306386992224,
      778447417301411654,  77890077030636524,   562272518474416451,
      617759205676632763,  137333390234583498,  847271379908091473,
      843204278942158126,  338984182620486881,  358287317722628763,
      893685844072834427,  371252050879235662,  466759492639294297,
      169735358743135221,  1025895978930331858, 1119837632754806494,
      102495632867771090,  570165268757777964,  890385541314698278,
      396930254673931570,  1131044024754944332, 761757922665814307,
      660572216313672066,  882715203237352097,  204696921447202932,
      8192237299084775,    409326672106986276,  871859211375214104,
      683969770428749805,  1007557589887202473, 1058613598685494981};

  std::vector<uint64_t> t_target_iter_ptr{
      754456001494305689,  1103969306386992224, 778447417301411654,
      77890077030636524,   562272518474416451,  617759205676632763,
      137333390234583498,  847271379908091473,  843204278942158126,
      338984182620486881,  358287317722628763,  893685844072834427,
      371252050879235662,  466759492639294297,  169735358743135221,
      1025895978930331858, 1119837632754806494, 102495632867771090,
      570165268757777964,  890385541314698278,  396930254673931570,
      1131044024754944332, 761757922665814307,  660572216313672066,
      882715203237352097,  204696921447202932,  8192237299084775,
      409326672106986276,  871859211375214104,  683969770428749805,
      1007557589887202473, 1058613598685494981};

  CkksSwitchKey(input.data(), t_target_iter_ptr.data(), coeff_count,
                decomp_modulus_size, key_modulus_size, rns_modulus_size,
                key_component_count, moduli.data(), hexl_key_vectors.data(),
                modswitch_factors.data());

  std::vector<uint64_t> expected_output{
      89296029533050855,   567993976793839274,  697003759686378746,
      954200861828558681,  689059820602871502,  584916558515910741,
      1113016444755385790, 516459831127873004,  853854391295677105,
      803745488422719022,  348933677108109560,  1042041991890481715,
      249754100961496944,  905908129921593063,  673977797089635231,
      170767802849348432,  304088977430009609,  445651998168994950,
      312087501328798066,  639799581779694831,  454743895520407562,
      1058792827229853104, 75780057043342395,   584325937127197146,
      644814876255694377,  523058110419679539,  418718157245016964,
      628771060933657117,  365105062057622652,  689317920107110551,
      1122739864436715515, 927797597840385390,  604718288130669178,
      35660497432980498,   622371763548914435,  970457320949190720,
      738770907185748198,  657824524642799580,  943718625650286270,
      753153158855748514,  37184128967339212,   873996122134404746,
      226555779311502898,  562475499750542681,  752409970800036216,
      708821234853973459,  809614432717950315,  1115565253826640226,
      221082875181656791,  956926195938203506,  942336604598200681,
      49168939851467655,   202063037837451976,  827436047316651204,
      223851251475980734,  769027623505616893,  128773783233783021,
      827862733453328407,  752577586897001479,  1034817794012654154,
      877127397759360655,  1083996636730543517, 745005168217272582,
      384338002660892880,  754456001494305689,  1103969306386992224,
      778447417301411654,  77890077030636524,   562272518474416451,
      617759205676632763,  137333390234583498,  847271379908091473,
      843204278942158126,  338984182620486881,  358287317722628763,
      893685844072834427,  371252050879235662,  466759492639294297,
      169735358743135221,  1025895978930331858, 1119837632754806494,
      102495632867771090,  570165268757777964,  890385541314698278,
      396930254673931570,  1131044024754944332, 761757922665814307,
      660572216313672066,  882715203237352097,  204696921447202932,
      8192237299084775,    409326672106986276,  871859211375214104,
      683969770428749805,  1007557589887202473, 1058613598685494981};

  AssertEqual(input, expected_output);
}

}  // namespace hexl
}  // namespace intel
