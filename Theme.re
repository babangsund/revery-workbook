open Revery;
open Revery.UI;

type t = {
  fontSize: int,
  inputWidth: int,
  inputHeight: int,
  orange: Color.t,
  textDark: Color.t,
  textLight: Color.t,
  fontFamily: string,
  borderColor: Color.t,
  backgroundColor: Color.t,
};

let default: t = {
  fontSize: 18,
  inputWidth: 200,
  inputHeight: 45,
  orange: Color.hex("#f90"),
  textDark: Color.hex("#333"),
  textLight: Color.hex("#fff"),
  borderColor: Color.hex("#fff"),
  fontFamily: "Roboto-Regular.ttf",
  backgroundColor: Color.hex("#232f3e"),
};