open Revery;
open Revery.UI;
open Revery.UI.Components;

let component = React.component("Root");

let make = () =>
  component(hooks => {
    (
      hooks,
      <View>
        <SelectEmployee onSetId={id => ()} onRegister={() => ()} />
        <TimeTable />
      </View>,
    )
  });

let createElement = (~children as _, ()) => make();