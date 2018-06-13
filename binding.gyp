{
  'targets': [
    {
      'target_name': 'node-icu-transliterator',
      'sources': [ 'node-icu-transliterator.cpp' ],
      'cflags!': [ '-fno-exceptions', '`icu-config --cppflags`' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'libraries': [ '`icu-config --detect-prefix --ldflags`' ],
      'include_dirs': [ "<!(node -e \"require('nan')\")" ],
      'conditions': [
        ['OS=="mac"', {
          'include_dirs': [ '/opt/local/include', '/usr/local/include' ],
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
            'OTHER_CFLAGS': [ '`icu-config --cppflags`' ]
          }
        }]
      ]
    }
  ]
}
