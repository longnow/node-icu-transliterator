{
  'targets': [
    {
      'target_name': 'node-icu-transliterator',
      'sources': [ 'node-icu-transliterator.cpp' ],
      'cflags!': [ '-fno-exceptions', '`pkg-config --cflags icu-i18n`' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'libraries': [ '`pkg-config --libs icu-i18n`' ],
      'include_dirs': [ "<!(node -e \"require('nan')\")" ],
      'conditions': [
        ['OS=="mac"', {
          'include_dirs': [ '/opt/local/include', '/usr/local/include' ],
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CFLAGS': [ '`pkg-config --cflags icu-i18n`' ]
          }
        }]
      ]
    }
  ]
}
