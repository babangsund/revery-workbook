open Revery;

type t = {
  inputWidth: int,
  inputHeight: int,
  orange: Color.t,
  textDark: Color.t,
  textLight: Color.t,
  backgroundColor: Color.t,
}

let default: t = {
  inputWidth: 200,
  inputHeight: 45,
  orange: Color.hex("#f90"),
  textDark: Color.hex("#333"),
  textLight: Color.hex("#fff"),
  backgroundColor: Color.hex("#232f3e"),
}

let create = () => default;
