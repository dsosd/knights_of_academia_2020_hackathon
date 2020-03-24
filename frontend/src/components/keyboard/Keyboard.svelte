<script>
  // TODO: Add keys to properties
  const keys1 = {
  '1': {
    'type': 'keystroke',
    'data': 'Alt Shift H',
    'color': '#d9345d'
  },
  '2': {
    'type': 'keystroke',
    'data': 'R',
    'color': '#32a887'
  },
  '3': {
    'type': 'keystroke',
    'data': 'Ctrl L',
    'color': '#d9345d'
  },
  '4': {
    'type': 'script',
    'data': 'echo Y',
    'color': '#32a887'
  },
  '5': {
    'type': 'keystroke',
    'data': 'Ctrl Shift B',
    'color': '#32a887'
  },
  '6': {
    'type': 'keystroke',
    'data': 'Alt Ctrl D',
    'color': '#32a887'
  },
  '7': {
    'type': 'keystroke',
    'data': 'Shift N',
    'color': '#32a887'
  },
  '8': {
    'type': 'keystroke',
    'data': 'K',
    'color': '#d9345d'
  },
  '9': {
    'type': 'keystroke',
    'data': 'G',
    'color': '#d9345d'
  },
  '10': {
    'type': 'script',
    'data': 'echo V',
    'color': '#d9345d'
  },
  '11': {
    'type': 'script',
    'data': 'echo X',
    'color': '#d9345d'
  },
  '12': {
    'type': 'script',
    'data': 'node',
    'color': '#d9345d'
  },
  '13': {
    'type': 'keystroke',
    'data': 'W',
    'color': '#d9345d'
  },
  '14': {
    'type': 'script',
    'data': 'echo S',
    'color': '#d9345d'
  },
  '15': {
    'type': 'script',
    'data': 'echo Z',
    'color': '#d9345d'
  },
  '16': {
    'type': 'script',
    'data': 'echo M',
    'color': '#d9345d'
  },
  '17': {
    'type': 'keystroke',
    'data': 'Q',
    'color': '#d9345d'
  },
  '18': {
    'type': 'script',
    'data': 'npm start',
    'color': '#32a887'
  },
  '19': {
    'type': 'script',
    'data': 'echo F',
    'color': '#d9345d'
  },
  '20': {
    'type': 'keystroke',
    'data': 'I',
    'color': '#d9345d'
  }
}

let keys = Object.entries(keys1).map(([id, v]) => ({id, ...v}))

</script>

<div id="keyboardWrapper">
  {#each keys as key}
  <div id="key" class={"_" + key.id}>
    <input type="color" bind:value={key.color}>

    <select class="select" bind:value={key.type}>
      <option>S</option>
      <option>K</option>
    </select>

    <input type="text" bind:value={key.data}>
  </div>
  {/each}

  <span class="index">
    <span>K - Keystroke</span>
    <span>S - Script</span>
  </span>

  <button id="save">
    <span>Save</span>
    <span class="material-icons">
      check_circle
    </span>
  </button>
</div>

<style src="./style.scss"></style>
