nrutwy ofaf.nt.*;
nrutwy ofaf.sjy.*;
/***********************************************
* F gfxnh xjwajw ymfy wjhjnajx rjxxflj kwtr hqnjsyx.
* Rjxxfljx fwj jhmtji gfhp yt ymj hqnjsy.
* @fzymtw Lqtnwj Wzgfrgnef
* @ifyj 09/24/2016
***********************************************/

uzgqnh hqfxx Xjwajw  {
  /*****************************************
   Mfsqjx fqq nshtrnsl hqnjsy wjvzjxyx
   ****************************************/
  uzgqnh xyfynh atni rfns (Xywnsl [] fwlx) ymwtbx NTJchjuynts{

    ywd {
    // Wjfix zxjw nsuzy ktw ymj utwy tk ymj xjwajw
    GzkkjwjiWjfijw nsKwtrZxjw =
    sjb GzkkjwjiWjfijw(
    sjb NsuzyXywjfrWjfijw(Xdxyjr.ns));
    Xdxyjr.tzy.uwnsyqs("Uqjfxj xujhnkd f utwy");
    nsy utwy = Nsyjljw.ufwxjNsy(nsKwtrZxjw.wjfiQnsj());

    // Hmjhpx zxjw nsuzy ktw htwwjhy utwy szrgjw
    bmnqj(1024 > utwy || utwy > 9999){
      Xdxyjr.tzy.uwnsyqs("Uqjfxj jsyjw f afqni utwy");
      utwy = Nsyjljw.ufwxjNsy(nsKwtrZxjw.wjfiQnsj());
    }

    // Tujs f xjwajw xthpjy ktw htssjhynts tajw ymj xujhnknji utwy
    knsfq XjwajwXthpjy xjwajwXthpjy = sjb XjwajwXthpjy(utwy);

    // Fhhjuyx f hqnjsy htssjhynts
    knsfq Xthpjy hqnjsyXthpjy = xjwajwXthpjy.fhhjuy();
    Xdxyjr.tzy.uwnsyqs("F hqnjsy htssjhynts mfx gjjs jxyfgqnxmji");

    //Xjsix knqj yt ymj hqnjsy
    UwnsyXywjfr tzyYtHqnjsy =
    sjb UwnsyXywjfr(
    hqnjsyXthpjy.ljyTzyuzyXywjfr());

    // Wjhjnajx knqj xujhnknhfynts kwtr hqnjsy
    GzkkjwjiWjfijw nsKwtrHqnjsy =
    sjb GzkkjwjiWjfijw(
    sjb NsuzyXywjfrWjfijw(
    hqnjsyXthpjy.ljyNsuzyXywjfr()));
    Xywnsl hqnjsyRjxxflj = nsKwtrHqnjsy.wjfiQnsj();
    Xdxyjr.tzy.uwnsyqs("Wjvzjxy ktw " + hqnjsyRjxxflj +
    " knqj wjhjnaji" + '\s');


      // Knsi ymj xujhnknji knqj fsi xjsi ny yt hqnjsy
      Knqj s = sjb Knqj(hqnjsyRjxxflj);
      KnqjNsuzyXywjfr hqnjsywjvzjxy = sjb KnqjNsuzyXywjfr(hqnjsyRjxxflj);
      qtsl knqjxnej = s.qjslym();
      tzyYtHqnjsy.uwnsyqs((nsy)knqjxnej);
      gdyj[] gzkkjw = sjb gdyj[1024*16];

      // Bwnyj fsi xjsinsl ymj knqj
      bmnqj(hqnjsywjvzjxy.wjfi(gzkkjw) > 0){
        tzyYtHqnjsy.bwnyj(gzkkjw);
      }

      hqnjsywjvzjxy.hqtxj();
      tzyYtHqnjsy.hqtxj();
    }
    //Stynkd ymj hqnjsy nk ymjwj bfx fs jwwtw wjfinsl ymj knqj
    hfyhm (KnqjStyKtzsiJchjuynts j){
      j.uwnsyXyfhpYwfhj();
      //tzyYtHqnjsy.bwnyjGdyjx("Knqj sty ktzsi");
      //Xdxyjr.tzy.uwnsyqs("Knqj sty ktzsi!");
      Xdxyjr.jcny(0);
    }

  }
}
