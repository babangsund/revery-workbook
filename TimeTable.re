open Revery;
open Revery.UI;
open Revery.UI.Components;

let component = React.component("TimeTable");

let make = () => component(hooks => {(hooks, <View />)});

let createElement = (~children as _, ()) => make();