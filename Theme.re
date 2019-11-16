open Revery;

type t = {
  fontSize: int,
  inputWidth: int,
  inputHeight: int,
  orange: Color.t,
  textDark: Color.t,
  textLight: Color.t,
  fontFamily: string,
  backgroundColor: Color.t,
};

let default: t = {
  fontFamily: "Roboto-Regular.ttf",
  fontSize: 18,
  inputWidth: 200,
  inputHeight: 45,
  orange: Color.hex("#f90"),
  textDark: Color.hex("#333"),
  textLight: Color.hex("#fff"),
  backgroundColor: Color.hex("#232f3e"),
};
